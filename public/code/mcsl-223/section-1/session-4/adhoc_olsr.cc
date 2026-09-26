/*
 * MCSL-223 Section 1, Session 4, Questions 8 and 9
 * Three-node mobile ad-hoc Wi-Fi network (RandomWaypoint) running OLSR.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/adhoc_olsr
 *
 *   n1 (10.1.1.1)   n2 (10.1.1.2)   n3 (10.1.1.3)
 *   802.11b ad-hoc, 11 Mbit/s, nodes move in a 100 m x 100 m box.
 *   Node index 0, 1, 2 in the code = n1, n2, n3 in the manual.
 *
 *   Q8: nodes, Wi-Fi channel/phy/mac, mobility, IP stack, addresses.
 *   Q9: OLSR through InternetStackHelper::SetRoutingHelper, routing
 *       tables printed at 5 s, 15 s and 30 s, one UDP echo n1 -> n3.
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/olsr-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("AdhocOlsr");

/*
 * PrintPositions: prints the current (x, y) of every node so the record
 * shows the nodes really move. Reschedules itself every 10 s.
 */
static void
PrintPositions(NodeContainer nodes)
{
    std::cout << "t=" << Simulator::Now().GetSeconds() << "s positions:";
    for (uint32_t i = 0; i < nodes.GetN(); ++i)
    {
        Vector p = nodes.Get(i)->GetObject<MobilityModel>()->GetPosition();
        std::cout << "  n" << i + 1 << " (" << p.x << ", " << p.y << ")";
    }
    std::cout << std::endl;
    Simulator::Schedule(Seconds(10.0), &PrintPositions, nodes);
}

/*
 * main: builds the MANET (Q8), installs OLSR (Q9), schedules routing-table
 * dumps and position prints, sends echo packets from n1 to n3 for 30 s.
 */
int
main(int argc, char* argv[])
{
    double simTime = 30.0;
    bool pcap = false;

    CommandLine cmd(__FILE__);
    cmd.AddValue("simTime", "Simulation length in seconds", simTime);
    cmd.AddValue("pcap", "Write per-node Wi-Fi pcap files", pcap);
    cmd.Parse(argc, argv);

    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // ---- Q8: wireless mobile ad-hoc network ----
    NodeContainer nodes;
    nodes.Create(3);

    // Physical layer and shared channel (log-distance propagation loss).
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    // 802.11b at a constant 11 Mbit/s so range is predictable (about 100 m).
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue("DsssRate11Mbps"),
                                 "ControlMode", StringValue("DsssRate11Mbps"));

    // Ad-hoc MAC: no access point, every node is a peer.
    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");
    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    // Mobility: RandomWaypoint inside a 100 m x 100 m box, 1 to 5 m/s, 2 s pause.
    ObjectFactory posFactory;
    posFactory.SetTypeId("ns3::RandomRectanglePositionAllocator");
    posFactory.Set("X", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"));
    posFactory.Set("Y", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"));
    Ptr<PositionAllocator> posAlloc = posFactory.Create()->GetObject<PositionAllocator>();

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
                              "Speed", StringValue("ns3::UniformRandomVariable[Min=1.0|Max=5.0]"),
                              "Pause", StringValue("ns3::ConstantRandomVariable[Constant=2.0]"),
                              "PositionAllocator", PointerValue(posAlloc));
    mobility.SetPositionAllocator(posAlloc);
    mobility.Install(nodes);

    // ---- Q9: OLSR routing ----
    OlsrHelper olsr;
    Ipv4StaticRoutingHelper staticRouting;
    Ipv4ListRoutingHelper list;
    list.Add(staticRouting, 0);
    list.Add(olsr, 10); // higher priority: OLSR is consulted first

    InternetStackHelper stack;
    stack.SetRoutingHelper(list); // must come before Install
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // Routing tables of all nodes at 5 s, 15 s and 30 s.
    Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>(&std::cout);
    olsr.PrintRoutingTableAllAt(Seconds(5.0), routingStream);
    olsr.PrintRoutingTableAllAt(Seconds(15.0), routingStream);
    olsr.PrintRoutingTableAllAt(Seconds(simTime), routingStream);

    // Traffic to prove the routes work: n1 echoes to n3 every 2 s.
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(2));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(simTime));

    UdpEchoClientHelper echoClient(interfaces.GetAddress(2), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(2.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(512));
    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(10.0)); // give OLSR time to converge
    clientApps.Stop(Seconds(simTime));

    if (pcap)
    {
        phy.EnablePcap("adhoc-olsr", devices);
    }

    Simulator::Schedule(Seconds(0.0), &PrintPositions, nodes);
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
