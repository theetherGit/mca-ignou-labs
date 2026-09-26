/*
 * MCSL-223 Section 1, Session 2, Question 3
 * End-to-end TCP throughput on the Session 1 link while the delay varies.
 *
 * Build: copy to ns-3.36+/scratch/ and run once per delay:
 *   ./ns3 run "scratch/throughput_vs_latency --delay=1ms"
 *   ./ns3 run "scratch/throughput_vs_latency --delay=10ms"
 *   ./ns3 run "scratch/throughput_vs_latency --delay=50ms"
 *   ./ns3 run "scratch/throughput_vs_latency --delay=100ms"
 *
 *   n0 (BulkSend) ---------- n1 (PacketSink, port 5000)
 *   10.1.1.1   5 Mbps, delay   10.1.1.2
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ThroughputVsLatency");

/*
 * main: builds the two-node link with the delay given on the command line,
 * runs a TCP bulk transfer from n0 to n1 for simTime seconds and prints
 * FlowMonitor statistics plus throughput = 8 * rxBytes / (tLastRx - tFirstTx).
 */
int
main(int argc, char* argv[])
{
    std::string delay = "10ms";
    double simTime = 10.0;

    CommandLine cmd(__FILE__);
    cmd.AddValue("delay", "One-way link delay, e.g. 1ms, 10ms, 50ms, 100ms", delay);
    cmd.AddValue("simTime", "Simulation length in seconds", simTime);
    cmd.Parse(argc, argv);

    // NewReno so the formula sheet describes what the simulator does.
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", StringValue("ns3::TcpNewReno"));

    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue(delay));
    NetDeviceContainer devices = p2p.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    uint16_t port = 5000;

    // Sink on n1 accepts the TCP connection and counts bytes.
    PacketSinkHelper sink("ns3::TcpSocketFactory",
                          InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApp = sink.Install(nodes.Get(1));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(simTime));

    // BulkSend on n0 sends as fast as TCP allows (MaxBytes 0 = unlimited).
    BulkSendHelper source("ns3::TcpSocketFactory",
                          InetSocketAddress(interfaces.GetAddress(1), port));
    source.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApp = source.Install(nodes.Get(0));
    sourceApp.Start(Seconds(1.0));
    sourceApp.Stop(Seconds(simTime));

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // Per-flow statistics. Flow 1 is data n0->n1, flow 2 is the ACK stream.
    monitor->CheckForLostPackets();
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());
    std::cout << "Delay = " << delay << std::endl;
    for (auto const& flow : monitor->GetFlowStats())
    {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(flow.first);
        const FlowMonitor::FlowStats& s = flow.second;
        double duration = s.timeLastRxPacket.GetSeconds() - s.timeFirstTxPacket.GetSeconds();
        double throughput = duration > 0 ? s.rxBytes * 8.0 / duration / 1e6 : 0;
        std::cout << "Flow " << flow.first << " (" << t.sourceAddress << " -> "
                  << t.destinationAddress << ")" << std::endl;
        std::cout << "  Tx Packets: " << s.txPackets << std::endl;
        std::cout << "  Rx Packets: " << s.rxPackets << std::endl;
        std::cout << "  Tx Bytes:   " << s.txBytes << std::endl;
        std::cout << "  Rx Bytes:   " << s.rxBytes << std::endl;
        std::cout << "  Lost:       " << s.lostPackets << std::endl;
        std::cout << "  Duration:   " << duration << " s" << std::endl;
        std::cout << "  Mean delay: "
                  << (s.rxPackets ? s.delaySum.GetSeconds() / s.rxPackets * 1000 : 0)
                  << " ms" << std::endl;
        std::cout << "  Throughput: " << throughput << " Mbit/s" << std::endl;
    }
    monitor->SerializeToXmlFile("throughput-" + delay + ".xml", false, false);

    Simulator::Destroy();
    return 0;
}
