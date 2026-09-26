/*
 * MCSL-223 Section 1, Session 5, Questions 10, 11 and 12
 * UDP client on n1, UDP server on n2 over the Session 4 ad-hoc Wi-Fi.
 * Writes bytes-received-versus-time to rx-bytes.dat and a pcap of n2's
 * Wi-Fi interface.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/wifi_udp_trace
 *   gnuplot rx_bytes.plt          (plot)
 *   wireshark wifi-udp-1-0.pcap   (n2 trace)
 *
 *   n1 (10.1.1.1, UdpClient) ---- 50 m ---- n2 (10.1.1.2, UdpServer port 9)
 *   Node index 0 and 1 in the code = n1 and n2 in the manual.
 *   Positions are fixed so the plot is repeatable; the Session 4 OLSR
 *   setup is kept so a third node could forward if added.
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/olsr-module.h"
#include "ns3/applications-module.h"
#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("WifiUdpTrace");

static uint64_t g_rxBytes = 0;      // bytes received at n2 so far
static std::ofstream g_traceFile;   // rx-bytes.dat

/*
 * RxTrace: called by the UdpServer "Rx" trace source for every packet
 * that reaches the application on n2. Adds its size to the running total.
 */
static void
RxTrace(Ptr<const Packet> packet)
{
    g_rxBytes += packet->GetSize();
}

/*
 * SampleRx: writes "time  cumulative_bytes" once per sample interval so
 * gnuplot can draw bytes received against time.
 */
static void
SampleRx(double interval)
{
    g_traceFile << Simulator::Now().GetSeconds() << "\t" << g_rxBytes << std::endl;
    Simulator::Schedule(Seconds(interval), &SampleRx, interval);
}

/*
 * main: builds the two-node ad-hoc Wi-Fi link (Q10), installs UdpServer on
 * n2 and UdpClient on n1 at 1024 B every 10 ms, records bytes over time
 * (Q11) and a pcap on n2's Wi-Fi device (Q12).
 */
int
main(int argc, char* argv[])
{
    double simTime = 10.0;
    uint32_t packetSize = 1024;
    double intervalMs = 10.0;     // 1024 B / 10 ms = 819.2 kbit/s
    double sample = 0.5;          // trace sample period in seconds
    double distance = 50.0;

    CommandLine cmd(__FILE__);
    cmd.AddValue("simTime", "Simulation length in seconds", simTime);
    cmd.AddValue("packetSize", "UDP payload in bytes", packetSize);
    cmd.AddValue("interval", "Client send interval in ms", intervalMs);
    cmd.AddValue("distance", "Distance between n1 and n2 in metres", distance);
    cmd.Parse(argc, argv);

    LogComponentEnable("UdpServer", LOG_LEVEL_INFO);

    // ---- Q10: two nodes on an ad-hoc Wi-Fi channel ----
    NodeContainer nodes;
    nodes.Create(2);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue("DsssRate11Mbps"),
                                 "ControlMode", StringValue("DsssRate11Mbps"));
    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");
    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    // Fixed positions: n1 at the origin, n2 `distance` metres along x.
    Ptr<ListPositionAllocator> positions = CreateObject<ListPositionAllocator>();
    positions->Add(Vector(0.0, 0.0, 0.0));
    positions->Add(Vector(distance, 0.0, 0.0));
    MobilityHelper mobility;
    mobility.SetPositionAllocator(positions);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);

    OlsrHelper olsr;
    InternetStackHelper stack;
    stack.SetRoutingHelper(olsr);
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // UDP server on n2 (port 9) and UDP client on n1.
    uint16_t port = 9;
    UdpServerHelper server(port);
    ApplicationContainer serverApp = server.Install(nodes.Get(1));
    serverApp.Start(Seconds(0.5));
    serverApp.Stop(Seconds(simTime));

    UdpClientHelper client(interfaces.GetAddress(1), port);
    client.SetAttribute("MaxPackets", UintegerValue(4294967295u)); // until Stop
    client.SetAttribute("Interval", TimeValue(MicroSeconds(static_cast<uint64_t>(intervalMs * 1000))));
    client.SetAttribute("PacketSize", UintegerValue(packetSize));
    ApplicationContainer clientApp = client.Install(nodes.Get(0));
    clientApp.Start(Seconds(1.0));
    clientApp.Stop(Seconds(simTime));

    // ---- Q11: bytes received versus time ----
    Ptr<UdpServer> udpServer = DynamicCast<UdpServer>(serverApp.Get(0));
    udpServer->TraceConnectWithoutContext("Rx", MakeCallback(&RxTrace));
    g_traceFile.open("rx-bytes.dat");
    g_traceFile << "# time(s)\tbytes_received_at_n2" << std::endl;
    Simulator::Schedule(Seconds(0.0), &SampleRx, sample);

    // ---- Q12: pcap on n2's Wi-Fi interface only -> wifi-udp-1-0.pcap ----
    phy.SetPcapDataLinkType(WifiPhyHelper::DLT_IEEE802_11_RADIO);
    phy.EnablePcap("wifi-udp", devices.Get(1));

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    std::cout << "Packets received at n2: " << udpServer->GetReceived()
              << ", lost: " << udpServer->GetLost() << std::endl;
    std::cout << "Bytes received at n2  : " << g_rxBytes << " in " << simTime - 1.0
              << " s = " << g_rxBytes * 8.0 / (simTime - 1.0) / 1e3 << " kbit/s" << std::endl;

    g_traceFile.close();
    Simulator::Destroy();
    return 0;
}
