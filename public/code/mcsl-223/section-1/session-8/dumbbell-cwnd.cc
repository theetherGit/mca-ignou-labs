/*
 * dumbbell-cwnd.cc  --  MCSL-223 Session 8, questions 19 to 22
 *
 * Purpose of the program:
 *   Rebuilds the Session 2 dumbbell with point-to-point links.  A TCP flow
 *   starts at 1 s (Q20).  At 20 s a UDP OnOff flow starts at Rate1, half of
 *   the bridge capacity (Q21).  Packets received per second at both sinks
 *   are written to packets.txt (Q19) and every change of the TCP congestion
 *   window is written to cwnd.txt through the ns-3 tracing mechanism (Q22).
 *
 * Topology (Session 2 dumbbell, all links point-to-point):
 *   n0 (TCP src) --10Mbps,1ms--\                     /--10Mbps,1ms-- n4 (TCP sink :8080)
 *                               n2 --1Mbps,10ms-- n3
 *   n1 (UDP src) --10Mbps,1ms--/    (the bridge)    \--10Mbps,1ms-- n5 (UDP sink :9000)
 *
 * Build and run (ns-3.36 or later):
 *   cp dumbbell-cwnd.cc scratch/
 *   ./ns3 run scratch/dumbbell-cwnd
 *   gnuplot plot_packets.gp          (packets.png)
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DumbbellCwnd");

static uint32_t g_tcpPackets = 0;  // packets seen by the TCP sink so far
static uint32_t g_udpPackets = 0;  // packets seen by the UDP sink so far

/*
 * RxPacket: PacketSink "Rx" trace sink.  Bound to one of the two counters
 * above; every delivered packet adds one.
 */
static void
RxPacket(uint32_t* counter, Ptr<const Packet> packet, const Address& from)
{
    (void)packet;
    (void)from;
    ++(*counter);
}

/*
 * SamplePackets: once per second writes "time tcpPackets udpPackets" for
 * the packets received during the last second, then re-schedules itself.
 */
static void
SamplePackets(Ptr<OutputStreamWrapper> stream)
{
    static uint32_t lastTcp = 0;
    static uint32_t lastUdp = 0;
    *stream->GetStream() << Simulator::Now().GetSeconds() << " " << (g_tcpPackets - lastTcp)
                         << " " << (g_udpPackets - lastUdp) << std::endl;
    lastTcp = g_tcpPackets;
    lastUdp = g_udpPackets;
    Simulator::Schedule(Seconds(1.0), &SamplePackets, stream);
}

/*
 * CwndChange: trace sink for the CongestionWindow attribute of the TCP
 * socket.  Writes "time newCwnd" (bytes) on every change.
 */
static void
CwndChange(Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
    (void)oldCwnd;
    *stream->GetStream() << Simulator::Now().GetSeconds() << " " << newCwnd << std::endl;
}

/*
 * TraceCwnd: connects CwndChange to the first TCP socket of node 0.  The
 * socket only exists after BulkSend starts at 1 s, so this is scheduled
 * at 1.001 s; connecting earlier would find no socket.
 */
static void
TraceCwnd(Ptr<OutputStreamWrapper> stream)
{
    Config::ConnectWithoutContext("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow",
                                  MakeBoundCallback(&CwndChange, stream));
}

/*
 * main: builds the dumbbell, installs TCP (1 s) and UDP (20 s) flows,
 * starts the two tracers and prints the totals at the end.
 */
int
main(int argc, char* argv[])
{
    std::string bridgeRate = "1Mbps";
    std::string rate1 = "500kb/s";  // half of the bridge
    double udpStart = 20.0;
    double simTime = 40.0;

    CommandLine cmd(__FILE__);
    cmd.AddValue("bridgeRate", "Data rate of the n2-n3 bridge", bridgeRate);
    cmd.AddValue("rate1", "UDP rate from udpStart onwards (Rate1)", rate1);
    cmd.AddValue("udpStart", "Time in seconds at which UDP starts", udpStart);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);
    cmd.Parse(argc, argv);

    Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue(1000));
    // NewReno halves cwnd on loss, as in the formula sheet (ns-3.35+ defaults to Cubic)
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));

    // ---- nodes: create left first so the TCP source is NodeList/0 --------
    NodeContainer left;
    left.Create(2);  // n0, n1
    NodeContainer routers;
    routers.Create(2);  // n2, n3
    NodeContainer right;
    right.Create(2);  // n4, n5

    PointToPointHelper access;
    access.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    access.SetChannelAttribute("Delay", StringValue("1ms"));

    PointToPointHelper bridge;
    bridge.SetDeviceAttribute("DataRate", StringValue(bridgeRate));
    bridge.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer d02 = access.Install(left.Get(0), routers.Get(0));
    NetDeviceContainer d12 = access.Install(left.Get(1), routers.Get(0));
    NetDeviceContainer d23 = bridge.Install(routers.Get(0), routers.Get(1));
    NetDeviceContainer d34 = access.Install(routers.Get(1), right.Get(0));
    NetDeviceContainer d35 = access.Install(routers.Get(1), right.Get(1));

    InternetStackHelper stack;
    stack.Install(left);
    stack.Install(routers);
    stack.Install(right);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    address.Assign(d02);
    address.SetBase("10.1.2.0", "255.255.255.0");
    address.Assign(d12);
    address.SetBase("10.1.3.0", "255.255.255.0");
    address.Assign(d23);
    address.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i34 = address.Assign(d34);
    address.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i35 = address.Assign(d35);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // ---- Q20: TCP n0 -> n4, starts at 1 s -------------------------------
    uint16_t tcpPort = 8080;
    PacketSinkHelper tcpSinkHelper("ns3::TcpSocketFactory",
                                   InetSocketAddress(Ipv4Address::GetAny(), tcpPort));
    ApplicationContainer tcpSink = tcpSinkHelper.Install(right.Get(0));
    tcpSink.Start(Seconds(0.0));
    tcpSink.Stop(Seconds(simTime));

    BulkSendHelper bulk("ns3::TcpSocketFactory", InetSocketAddress(i34.GetAddress(1), tcpPort));
    bulk.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer tcpSrc = bulk.Install(left.Get(0));
    tcpSrc.Start(Seconds(1.0));
    tcpSrc.Stop(Seconds(simTime));

    // ---- Q21: UDP n1 -> n5 at Rate1, starts at 20 s ----------------------
    uint16_t udpPort = 9000;
    PacketSinkHelper udpSinkHelper("ns3::UdpSocketFactory",
                                   InetSocketAddress(Ipv4Address::GetAny(), udpPort));
    ApplicationContainer udpSink = udpSinkHelper.Install(right.Get(1));
    udpSink.Start(Seconds(0.0));
    udpSink.Stop(Seconds(simTime));

    OnOffHelper onoff("ns3::UdpSocketFactory", InetSocketAddress(i35.GetAddress(1), udpPort));
    onoff.SetConstantRate(DataRate(rate1), 1000);
    ApplicationContainer udpSrc = onoff.Install(left.Get(1));
    udpSrc.Start(Seconds(udpStart));
    udpSrc.Stop(Seconds(simTime));

    // ---- Q19: packets received per second at both sinks ------------------
    tcpSink.Get(0)->TraceConnectWithoutContext("Rx", MakeBoundCallback(&RxPacket, &g_tcpPackets));
    udpSink.Get(0)->TraceConnectWithoutContext("Rx", MakeBoundCallback(&RxPacket, &g_udpPackets));

    AsciiTraceHelper ascii;
    Simulator::Schedule(Seconds(1.0), &SamplePackets, ascii.CreateFileStream("packets.txt"));

    // ---- Q22: cwnd trace, connected just after the socket exists ---------
    Simulator::Schedule(Seconds(1.001), &TraceCwnd, ascii.CreateFileStream("cwnd.txt"));

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // ---- report ---------------------------------------------------------
    Ptr<PacketSink> ts = DynamicCast<PacketSink>(tcpSink.Get(0));
    Ptr<PacketSink> us = DynamicCast<PacketSink>(udpSink.Get(0));
    std::cout << "TCP sink n4: " << ts->GetTotalRx() << " bytes, " << g_tcpPackets
              << " packets over " << simTime - 1.0 << " s = "
              << ts->GetTotalRx() * 8.0 / (simTime - 1.0) / 1000.0 << " kbit/s" << std::endl;
    std::cout << "UDP sink n5: " << us->GetTotalRx() << " bytes, " << g_udpPackets
              << " packets over " << simTime - udpStart << " s = "
              << us->GetTotalRx() * 8.0 / (simTime - udpStart) / 1000.0 << " kbit/s" << std::endl;

    Simulator::Destroy();
    return 0;
}
