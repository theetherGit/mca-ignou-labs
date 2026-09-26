/*
 * MCSL-223 Section 1, Session 2, Question 4
 * Dumbbell topology with point-to-point links only.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/dumbbell
 *
 *   n0 (client) --\                       /-- n4 (server)
 *                  n2 ---- bridge ---- n3
 *   n1 (client) --/    2 Mbps, 10 ms     \-- n5 (server)
 *
 * Access links 10 Mbps, 1 ms. Subnets:
 *   n0-n2 10.1.1.0/24   n1-n2 10.1.2.0/24   n2-n3 10.1.3.0/24
 *   n3-n4 10.1.4.0/24   n3-n5 10.1.5.0/24
 * The manual calls the routers n1 and n2; here they are n2 and n3 so the
 * node index matches the NodeContainer index.
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Dumbbell");

/*
 * main: creates six nodes, five point-to-point links, five subnets,
 * fills the routing tables with global routing and verifies the paths with
 * one UDP echo from each client to its server.
 */
int
main(int argc, char* argv[])
{
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);

    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(6);

    // Node pairs for the five links.
    NodeContainer n0n2(nodes.Get(0), nodes.Get(2));
    NodeContainer n1n2(nodes.Get(1), nodes.Get(2));
    NodeContainer n2n3(nodes.Get(2), nodes.Get(3));
    NodeContainer n3n4(nodes.Get(3), nodes.Get(4));
    NodeContainer n3n5(nodes.Get(3), nodes.Get(5));

    PointToPointHelper access;
    access.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    access.SetChannelAttribute("Delay", StringValue("1ms"));

    PointToPointHelper bridge;
    bridge.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
    bridge.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer d0d2 = access.Install(n0n2);
    NetDeviceContainer d1d2 = access.Install(n1n2);
    NetDeviceContainer d2d3 = bridge.Install(n2n3);
    NetDeviceContainer d3d4 = access.Install(n3n4);
    NetDeviceContainer d3d5 = access.Install(n3n5);

    InternetStackHelper stack;
    stack.Install(nodes);

    // One subnet per link.
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i0i2 = address.Assign(d0d2);
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i1i2 = address.Assign(d1d2);
    address.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer i2i3 = address.Assign(d2d3);
    address.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i4 = address.Assign(d3d4);
    address.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i5 = address.Assign(d3d5);

    // Routers n2 and n3 need routes to every subnet.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    std::cout << "n0 " << i0i2.GetAddress(0) << "  n1 " << i1i2.GetAddress(0)
              << "  n2 " << i0i2.GetAddress(1) << "/" << i1i2.GetAddress(1) << "/"
              << i2i3.GetAddress(0) << "  n3 " << i2i3.GetAddress(1) << "/"
              << i3i4.GetAddress(0) << "/" << i3i5.GetAddress(0) << "  n4 "
              << i3i4.GetAddress(1) << "  n5 " << i3i5.GetAddress(1) << std::endl;

    // Echo servers on n4 and n5; one echo from n0 to n4 and from n1 to n5.
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer servers = echoServer.Install(NodeContainer(nodes.Get(4), nodes.Get(5)));
    servers.Start(Seconds(1.0));
    servers.Stop(Seconds(10.0));

    UdpEchoClientHelper client0(i3i4.GetAddress(1), 9);
    client0.SetAttribute("MaxPackets", UintegerValue(1));
    client0.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer c0 = client0.Install(nodes.Get(0));
    c0.Start(Seconds(2.0));
    c0.Stop(Seconds(10.0));

    UdpEchoClientHelper client1(i3i5.GetAddress(1), 9);
    client1.SetAttribute("MaxPackets", UintegerValue(1));
    client1.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer c1 = client1.Install(nodes.Get(1));
    c1.Start(Seconds(3.0));
    c1.Stop(Seconds(10.0));

    // Print n2's routing table at 1 s to show the global routes.
    Ptr<OutputStreamWrapper> routing = Create<OutputStreamWrapper>(&std::cout);
    Ipv4GlobalRoutingHelper::PrintRoutingTableAt(Seconds(1.0), nodes.Get(2), routing);

    bridge.EnablePcapAll("dumbbell");

    Simulator::Stop(Seconds(10.0));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
