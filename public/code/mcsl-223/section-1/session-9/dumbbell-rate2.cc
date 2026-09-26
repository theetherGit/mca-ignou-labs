/*
 * dumbbell-rate2.cc  --  MCSL-223 Session 9, questions 23 and 24
 *
 * Purpose of the program:
 *   The Session 8 dumbbell, extended: TCP starts at 1 s, UDP starts at 20 s
 *   at Rate1 (500 kb/s, half the 1 Mbit/s bridge) and at 30 s the UDP rate
 *   is raised to Rate2 (1 Mbit/s, the whole bridge) by a scheduled event
 *   that changes the OnOff application's DataRate attribute (Q23).  The
 *   congestion window of the TCP socket is traced to cwnd.txt and plotted
 *   with plot_cwnd.py, which marks Rate1 and Rate2 (Q24).
 *
 * Topology (Session 2 dumbbell, all links point-to-point):
 *   n0 (TCP src) --10Mbps,1ms--\                     /--10Mbps,1ms-- n4 (TCP sink :8080)
 *                               n2 --1Mbps,10ms-- n3
 *   n1 (UDP src) --10Mbps,1ms--/    (the bridge)    \--10Mbps,1ms-- n5 (UDP sink :9000)
 *
 * Build and run (ns-3.36 or later):
 *   cp dumbbell-rate2.cc scratch/
 *   ./ns3 run scratch/dumbbell-rate2
 *   python3 plot_cwnd.py cwnd.txt cwnd.png
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DumbbellRate2");

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
 * TraceCwnd: connects CwndChange to the first TCP socket of node 0.
 * Scheduled at 1.001 s, just after BulkSend has created the socket.
 */
static void
TraceCwnd(Ptr<OutputStreamWrapper> stream)
{
    Config::ConnectWithoutContext("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow",
                                  MakeBoundCallback(&CwndChange, stream));
}

/*
 * ChangeRate: scheduled at 30 s.  Sets the DataRate attribute of the
 * running OnOff application; the next packet interval uses the new rate.
 */
static void
ChangeRate(Ptr<Application> app, DataRate rate)
{
    app->SetAttribute("DataRate", DataRateValue(rate));
    std::cout << Simulator::Now().GetSeconds() << " s: UDP rate changed to " << rate
              << std::endl;
}

/*
 * main: builds the dumbbell, installs the flows, schedules the rate change
 * and the cwnd tracer, and prints the totals at the end.
 */
int
main(int argc, char* argv[])
{
    std::string bridgeRate = "1Mbps";
    std::string rate1 = "500kb/s";  // half of the bridge
    std::string rate2 = "1Mbps";    // whole bridge
    double udpStart = 20.0;
    double rate2Time = 30.0;
    double simTime = 45.0;

    CommandLine cmd(__FILE__);
    cmd.AddValue("bridgeRate", "Data rate of the n2-n3 bridge", bridgeRate);
    cmd.AddValue("rate1", "UDP rate from udpStart (Rate1)", rate1);
    cmd.AddValue("rate2", "UDP rate from rate2Time (Rate2)", rate2);
    cmd.AddValue("udpStart", "Time in seconds at which UDP starts", udpStart);
    cmd.AddValue("rate2Time", "Time in seconds at which UDP switches to Rate2", rate2Time);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);
    cmd.Parse(argc, argv);

    Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue(1000));
    // NewReno halves cwnd on loss, as in the formula sheet (ns-3.35+ defaults to Cubic)
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));

    // ---- nodes: left first so the TCP source is NodeList/0 ---------------
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

    // ---- TCP n0 -> n4 from 1 s ------------------------------------------
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

    // ---- UDP n1 -> n5 at Rate1 from 20 s --------------------------------
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

    // ---- Q23: switch the same OnOff application to Rate2 at 30 s ---------
    Simulator::Schedule(Seconds(rate2Time), &ChangeRate, udpSrc.Get(0), DataRate(rate2));

    // ---- Q24: cwnd trace, connected just after the socket exists ---------
    AsciiTraceHelper ascii;
    Simulator::Schedule(Seconds(1.001), &TraceCwnd, ascii.CreateFileStream("cwnd.txt"));

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // ---- report ---------------------------------------------------------
    Ptr<PacketSink> ts = DynamicCast<PacketSink>(tcpSink.Get(0));
    Ptr<PacketSink> us = DynamicCast<PacketSink>(udpSink.Get(0));
    std::cout << "TCP sink n4: " << ts->GetTotalRx() << " bytes over " << simTime - 1.0
              << " s = " << ts->GetTotalRx() * 8.0 / (simTime - 1.0) / 1000.0 << " kbit/s"
              << std::endl;
    std::cout << "UDP sink n5: " << us->GetTotalRx() << " bytes over " << simTime - udpStart
              << " s = " << us->GetTotalRx() * 8.0 / (simTime - udpStart) / 1000.0 << " kbit/s"
              << std::endl;

    Simulator::Destroy();
    return 0;
}
