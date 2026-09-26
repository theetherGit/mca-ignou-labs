/*
 * MCSL-223 Section 1, Session 3, Questions 5, 6 and 7
 * Two TCP connections across the Session 2 dumbbell, with packet-flow
 * monitoring by pcap and FlowMonitor.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/dumbbell_tcp
 *
 *   n0 --10Mbps,1ms--\                        /--10Mbps,1ms-- n4
 *                     n2 --2Mbps,10ms-- n3
 *   n1 --10Mbps,1ms--/                        \--10Mbps,1ms-- n5
 *
 *   Q5: TCP n0 (BulkSend) -> n4 (PacketSink, port 8080)
 *   Q6: TCP n1 (BulkSend) -> n5 (PacketSink, port 8081)
 *   Q7: both start at 1 s; pcap on the bridge, FlowMonitor on all nodes.
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DumbbellTcp");

/*
 * InstallTcpPair: installs a PacketSink on server (port) and a BulkSend on
 * client aimed at serverAddr:port. Returns the sink so main can read
 * GetTotalRx() after the run. This is the "TCP socket instance" of Q5/Q6.
 */
static Ptr<PacketSink>
InstallTcpPair(Ptr<Node> client, Ptr<Node> server, Ipv4Address serverAddr,
               uint16_t port, double start, double stop)
{
    PacketSinkHelper sinkHelper("ns3::TcpSocketFactory",
                                InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApp = sinkHelper.Install(server);
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(stop));

    BulkSendHelper source("ns3::TcpSocketFactory", InetSocketAddress(serverAddr, port));
    source.SetAttribute("MaxBytes", UintegerValue(0)); // unlimited
    source.SetAttribute("SendSize", UintegerValue(1024));
    ApplicationContainer sourceApp = source.Install(client);
    sourceApp.Start(Seconds(start));
    sourceApp.Stop(Seconds(stop));

    return DynamicCast<PacketSink>(sinkApp.Get(0));
}

/*
 * main: builds the dumbbell (same as Session 2), installs the two TCP
 * pairs, enables pcap on the bridge devices and FlowMonitor everywhere,
 * runs 10 s and prints bytes at each sink plus per-flow statistics.
 */
int
main(int argc, char* argv[])
{
    double simTime = 10.0;
    CommandLine cmd(__FILE__);
    cmd.AddValue("simTime", "Simulation length in seconds", simTime);
    cmd.Parse(argc, argv);

    Config::SetDefault("ns3::TcpL4Protocol::SocketType", StringValue("ns3::TcpNewReno"));

    NodeContainer nodes;
    nodes.Create(6);

    PointToPointHelper access;
    access.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    access.SetChannelAttribute("Delay", StringValue("1ms"));
    PointToPointHelper bridge;
    bridge.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
    bridge.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer d0d2 = access.Install(nodes.Get(0), nodes.Get(2));
    NetDeviceContainer d1d2 = access.Install(nodes.Get(1), nodes.Get(2));
    NetDeviceContainer d2d3 = bridge.Install(nodes.Get(2), nodes.Get(3));
    NetDeviceContainer d3d4 = access.Install(nodes.Get(3), nodes.Get(4));
    NetDeviceContainer d3d5 = access.Install(nodes.Get(3), nodes.Get(5));

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    address.Assign(d0d2);
    address.SetBase("10.1.2.0", "255.255.255.0");
    address.Assign(d1d2);
    address.SetBase("10.1.3.0", "255.255.255.0");
    address.Assign(d2d3);
    address.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i4 = address.Assign(d3d4);
    address.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i5 = address.Assign(d3d5);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Q5: first pair n0 -> n4. Q6: second pair n1 -> n5.
    Ptr<PacketSink> sink4 =
        InstallTcpPair(nodes.Get(0), nodes.Get(4), i3i4.GetAddress(1), 8080, 1.0, simTime);
    Ptr<PacketSink> sink5 =
        InstallTcpPair(nodes.Get(1), nodes.Get(5), i3i5.GetAddress(1), 8081, 1.0, simTime);

    // Q7: monitoring. pcap on the bridge (dumbbell-tcp-2-2.pcap, dumbbell-tcp-3-0.pcap).
    bridge.EnablePcap("dumbbell-tcp", d2d3);
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    double active = simTime - 1.0;
    std::cout << "Sink n4 (port 8080): " << sink4->GetTotalRx() << " bytes, "
              << sink4->GetTotalRx() * 8.0 / active / 1e6 << " Mbit/s" << std::endl;
    std::cout << "Sink n5 (port 8081): " << sink5->GetTotalRx() << " bytes, "
              << sink5->GetTotalRx() * 8.0 / active / 1e6 << " Mbit/s" << std::endl;

    monitor->CheckForLostPackets();
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());
    for (auto const& flow : monitor->GetFlowStats())
    {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(flow.first);
        const FlowMonitor::FlowStats& s = flow.second;
        double duration = s.timeLastRxPacket.GetSeconds() - s.timeFirstTxPacket.GetSeconds();
        std::cout << "Flow " << flow.first << " (" << t.sourceAddress << ":" << t.sourcePort
                  << " -> " << t.destinationAddress << ":" << t.destinationPort << ")"
                  << std::endl;
        std::cout << "  Tx Packets: " << s.txPackets << "  Rx Packets: " << s.rxPackets
                  << "  Lost: " << s.lostPackets << std::endl;
        std::cout << "  Rx Bytes:   " << s.rxBytes << "  Throughput: "
                  << (duration > 0 ? s.rxBytes * 8.0 / duration / 1e6 : 0) << " Mbit/s"
                  << std::endl;
    }
    monitor->SerializeToXmlFile("dumbbell-tcp.xml", false, false);

    Simulator::Destroy();
    return 0;
}
