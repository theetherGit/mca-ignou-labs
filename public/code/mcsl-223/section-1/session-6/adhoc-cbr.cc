/*
 * adhoc-cbr.cc  --  MCSL-223 Session 6, questions 13 to 15
 *
 * Purpose of the program:
 *   Two 802.11a ad-hoc nodes are placed at fixed 3D coordinates
 *   (ConstantPositionMobilityModel fed by a ListPositionAllocator).
 *   Node 0 runs a UdpClient (Q14) and a constant bit rate OnOff source (Q15);
 *   node 1 runs the matching UdpServer and a PacketSink.  At the end the
 *   program prints the positions, the distance, the packets the UdpServer
 *   counted and the bytes the CBR sink delivered.
 *
 * Topology:
 *        n0 (0, 0, 1.5) m  ~~~~ 802.11a ad-hoc, 6 Mbit/s ~~~~  n1 (d, 0, 1.5) m
 *        UdpClient  --> port 9  --> UdpServer
 *        OnOff CBR  --> port 10 --> PacketSink
 *
 * Build and run (ns-3.36 or later):
 *   cp adhoc-cbr.cc scratch/
 *   ./ns3 run "scratch/adhoc-cbr --distance=50"
 *   ./ns3 run "scratch/adhoc-cbr --distance=100"
 *   ./ns3 run "scratch/adhoc-cbr --distance=150"
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("AdhocCbr");

/*
 * main: builds the two-node ad-hoc network, installs the applications,
 * runs for simTime seconds and prints the delivery figures.
 */
int
main(int argc, char* argv[])
{
    double distance = 50.0;        // metres between the nodes along x
    double height = 1.5;           // antenna height, the z coordinate
    double simTime = 10.0;         // seconds
    std::string cbrRate = "500kb/s";
    uint32_t cbrPacketSize = 500;  // bytes, so 500 kb/s is one packet every 8 ms
    bool verbose = false;

    CommandLine cmd(__FILE__);
    cmd.AddValue("distance", "Distance between the two nodes in metres", distance);
    cmd.AddValue("height", "Antenna height (z coordinate) in metres", height);
    cmd.AddValue("cbrRate", "Constant bit rate of the OnOff source", cbrRate);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);
    cmd.AddValue("verbose", "Print UdpClient and UdpServer log lines", verbose);
    cmd.Parse(argc, argv);

    if (verbose)
    {
        LogComponentEnable("UdpClient", LOG_LEVEL_INFO);
        LogComponentEnable("UdpServer", LOG_LEVEL_INFO);
    }

    // ---- Q13: two nodes at fixed 3D positions --------------------------
    NodeContainer nodes;
    nodes.Create(2);

    Ptr<ListPositionAllocator> positions = CreateObject<ListPositionAllocator>();
    positions->Add(Vector(0.0, 0.0, height));       // node 0
    positions->Add(Vector(distance, 0.0, height));  // node 1

    MobilityHelper mobility;
    mobility.SetPositionAllocator(positions);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);

    // ---- Q13: 802.11a ad-hoc Wi-Fi at a fixed 6 Mbit/s ------------------
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211a);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue("OfdmRate6Mbps"),
                                 "ControlMode", StringValue("OfdmRate6Mbps"));

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer ifaces = address.Assign(devices);

    // ---- Q14: UdpServer on node 1, UdpClient on node 0 -------------------
    uint16_t udpPort = 9;
    uint32_t clientPackets = 900;

    UdpServerHelper server(udpPort);
    ApplicationContainer serverApp = server.Install(nodes.Get(1));
    serverApp.Start(Seconds(0.0));
    serverApp.Stop(Seconds(simTime));

    UdpClientHelper client(ifaces.GetAddress(1), udpPort);
    client.SetAttribute("MaxPackets", UintegerValue(clientPackets));
    client.SetAttribute("Interval", TimeValue(MilliSeconds(10)));
    client.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer clientApp = client.Install(nodes.Get(0));
    clientApp.Start(Seconds(1.0));
    clientApp.Stop(Seconds(simTime));

    // ---- Q15: constant bit rate flow node 0 -> node 1 --------------------
    uint16_t cbrPort = 10;

    OnOffHelper onoff("ns3::UdpSocketFactory",
                      InetSocketAddress(ifaces.GetAddress(1), cbrPort));
    onoff.SetConstantRate(DataRate(cbrRate), cbrPacketSize);  // OnTime 1, OffTime 0
    ApplicationContainer cbrApp = onoff.Install(nodes.Get(0));
    cbrApp.Start(Seconds(1.0));
    cbrApp.Stop(Seconds(simTime));

    PacketSinkHelper sinkHelper("ns3::UdpSocketFactory",
                                InetSocketAddress(Ipv4Address::GetAny(), cbrPort));
    ApplicationContainer sinkApp = sinkHelper.Install(nodes.Get(1));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(simTime));

    // pcap of node 1's Wi-Fi interface, for Wireshark
    phy.EnablePcap("adhoc-cbr", devices.Get(1));

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // ---- report ---------------------------------------------------------
    Ptr<MobilityModel> m0 = nodes.Get(0)->GetObject<MobilityModel>();
    Ptr<MobilityModel> m1 = nodes.Get(1)->GetObject<MobilityModel>();
    Vector p0 = m0->GetPosition();
    Vector p1 = m1->GetPosition();

    Ptr<UdpServer> udpServer = DynamicCast<UdpServer>(serverApp.Get(0));
    Ptr<PacketSink> sink = DynamicCast<PacketSink>(sinkApp.Get(0));
    double active = simTime - 1.0;  // both sources run from 1 s to simTime

    std::cout << "Node 0 at (" << p0.x << ", " << p0.y << ", " << p0.z << ") m, "
              << "node 1 at (" << p1.x << ", " << p1.y << ", " << p1.z << ") m, "
              << "distance " << m0->GetDistanceFrom(m1) << " m" << std::endl;
    std::cout << "UdpClient : sent " << clientPackets << " packets of 1024 bytes" << std::endl;
    std::cout << "UdpServer : received " << udpServer->GetReceived() << " packets, lost "
              << udpServer->GetLost() << std::endl;
    std::cout << "CBR sink  : received " << sink->GetTotalRx() << " bytes in " << active
              << " s = " << sink->GetTotalRx() * 8.0 / active / 1000.0 << " kbit/s"
              << std::endl;

    Simulator::Destroy();
    return 0;
}
