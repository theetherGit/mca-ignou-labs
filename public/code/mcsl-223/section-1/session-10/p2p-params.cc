/*
 * p2p-params.cc  --  MCSL-223 Session 10, question 25
 *
 * Purpose of the program:
 *   A two-node point-to-point link whose bandwidth, one-way delay, random
 *   packet loss rate, queue size at node 0 and simulation time are all
 *   command-line parameters with the defaults given in the manual.  A TCP
 *   bulk transfer runs from node 0 to node 1 and both interfaces are
 *   captured to pcap so the average TCP throughput can be read in
 *   Wireshark (Statistics, Conversations, TCP).
 *
 * Topology:
 *   n0 (BulkSend) ---- bandwidth, delay, DropTail queue, RateErrorModel ---- n1 (PacketSink :8080)
 *
 * Build and run (ns-3.36 or later):
 *   cp p2p-params.cc scratch/
 *   ./ns3 run scratch/p2p-params
 *   ./ns3 run "scratch/p2p-params --bandwidth=2Mbps --delay=20ms --lossRate=0.001 --queueSize=5 --simTime=20"
 *   wireshark p2p-params-1-0.pcap
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("P2pParams");

/*
 * main: reads the five parameters, builds the link, attaches the loss
 * model and the queue, runs a TCP bulk transfer and prints the bytes the
 * sink received together with the throughput for comparison with Wireshark.
 */
int
main(int argc, char* argv[])
{
    std::string bandwidth = "5Mbps";  // link bandwidth
    std::string delay = "5ms";        // one-way delay
    double lossRate = 0.000001;       // random per-packet loss, not queue drops
    uint32_t queueSize = 10;          // packets in the DropTail queue at node 0
    double simTime = 10.0;            // seconds

    CommandLine cmd(__FILE__);
    cmd.AddValue("bandwidth", "Link bandwidth between the two nodes", bandwidth);
    cmd.AddValue("delay", "One way delay of the link", delay);
    cmd.AddValue("lossRate", "Loss rate of packets on the link (per packet)", lossRate);
    cmd.AddValue("queueSize", "Queue size of the buffer at node 0 in packets", queueSize);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);
    cmd.Parse(argc, argv);

    // Ethernet-sized segments; ns-3 defaults to 536 bytes
    Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue(1448));
    // NewReno halves cwnd on loss, as in the formula sheet (ns-3.35+ defaults to Cubic)
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));

    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue(bandwidth));
    p2p.SetChannelAttribute("Delay", StringValue(delay));
    p2p.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(std::to_string(queueSize) + "p"));
    NetDeviceContainer devices = p2p.Install(nodes);

    // random losses on the link, applied where node 1 receives
    Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
    em->SetAttribute("ErrorRate", DoubleValue(lossRate));
    em->SetAttribute("ErrorUnit", StringValue("ERROR_UNIT_PACKET"));
    devices.Get(1)->SetAttribute("ReceiveErrorModel", PointerValue(em));

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer ifaces = address.Assign(devices);

    uint16_t port = 8080;
    PacketSinkHelper sinkHelper("ns3::TcpSocketFactory",
                                InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApp = sinkHelper.Install(nodes.Get(1));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(simTime));

    BulkSendHelper bulk("ns3::TcpSocketFactory", InetSocketAddress(ifaces.GetAddress(1), port));
    bulk.SetAttribute("MaxBytes", UintegerValue(0));  // keep sending until stopped
    ApplicationContainer srcApp = bulk.Install(nodes.Get(0));
    srcApp.Start(Seconds(0.0));
    srcApp.Stop(Seconds(simTime));

    // p2p-params-0-0.pcap (sender side) and p2p-params-1-0.pcap (receiver side)
    p2p.EnablePcapAll("p2p-params");

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    Ptr<PacketSink> sink = DynamicCast<PacketSink>(sinkApp.Get(0));
    std::cout << "bandwidth=" << bandwidth << " delay=" << delay << " lossRate=" << lossRate
              << " queueSize=" << queueSize << "p simTime=" << simTime << "s" << std::endl;
    std::cout << "Sink received " << sink->GetTotalRx() << " bytes in " << simTime
              << " s: goodput " << sink->GetTotalRx() * 8.0 / simTime / 1e6 << " Mbit/s"
              << std::endl;

    Simulator::Destroy();
    return 0;
}
