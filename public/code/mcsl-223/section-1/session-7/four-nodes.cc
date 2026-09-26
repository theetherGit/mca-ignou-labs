/*
 * four-nodes.cc  --  MCSL-223 Session 7, questions 16 to 18
 *
 * Purpose of the program:
 *   Four nodes share one 2 Mbit/s CSMA bus.  Two TCP pairs and two UDP pairs
 *   run at the same time so that all four flows compete for the bus.  Every
 *   0.5 s the cumulative bytes received at each of the four sinks is written
 *   to its own trace file (tcp1-bytes.txt, tcp2-bytes.txt, udp1-bytes.txt,
 *   udp2-bytes.txt); plot_bytes.gp draws the four series on one chart.
 *
 * Topology (CSMA bus, 2 Mbit/s, 6560 ns):
 *        n0 -------- n1 -------- n2 -------- n3
 *        TCP1  n0 -> n2  port 8080  (BulkSend  -> PacketSink)
 *        TCP2  n1 -> n3  port 8081  (BulkSend  -> PacketSink)
 *        UDP1  n2 -> n0  port 9000  (OnOff 500 kb/s -> PacketSink)
 *        UDP2  n3 -> n1  port 9001  (OnOff 500 kb/s -> PacketSink)
 *   Each node sends exactly one flow, so the bus is the only shared resource.
 *
 * Build and run (ns-3.36 or later):
 *   cp four-nodes.cc scratch/
 *   ./ns3 run scratch/four-nodes
 *   gnuplot plot_bytes.gp        (produces bytes.png)
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"

#include <vector>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FourNodes");

/*
 * SampleBytes: writes "time bytes" for every sink into its own stream and
 * re-schedules itself 0.5 s later.  GetTotalRx() is the cumulative byte
 * count that PacketSink keeps for us.
 */
static void
SampleBytes(ApplicationContainer sinks, std::vector<Ptr<OutputStreamWrapper>> streams)
{
    for (uint32_t i = 0; i < sinks.GetN(); ++i)
    {
        Ptr<PacketSink> sink = DynamicCast<PacketSink>(sinks.Get(i));
        *streams[i]->GetStream() << Simulator::Now().GetSeconds() << " " << sink->GetTotalRx()
                                 << std::endl;
    }
    Simulator::Schedule(Seconds(0.5), &SampleBytes, sinks, streams);
}

/*
 * main: builds the bus, installs the four sender/sink pairs, starts the
 * sampler, runs for 10 s and prints bytes and throughput per sink.
 */
int
main(int argc, char* argv[])
{
    std::string busRate = "2Mbps";
    std::string udpRate = "500kb/s";
    double simTime = 10.0;

    CommandLine cmd(__FILE__);
    cmd.AddValue("busRate", "CSMA bus data rate", busRate);
    cmd.AddValue("udpRate", "Rate of each UDP OnOff source", udpRate);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);
    cmd.Parse(argc, argv);

    // ---- Q16: four nodes on one CSMA bus ---------------------------------
    NodeContainer nodes;
    nodes.Create(4);

    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue(busRate));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));
    NetDeviceContainer devices = csma.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer ifaces = address.Assign(devices);

    // sender index, receiver index, port, "tcp" or "udp"
    struct Pair
    {
        uint32_t from;
        uint32_t to;
        uint16_t port;
        bool tcp;
        std::string name;
    };
    std::vector<Pair> pairs = {{0, 2, 8080, true, "tcp1"},
                               {1, 3, 8081, true, "tcp2"},
                               {2, 0, 9000, false, "udp1"},
                               {3, 1, 9001, false, "udp2"}};

    ApplicationContainer sinks;
    std::vector<Ptr<OutputStreamWrapper>> streams;
    AsciiTraceHelper ascii;

    for (const Pair& p : pairs)
    {
        std::string factory = p.tcp ? "ns3::TcpSocketFactory" : "ns3::UdpSocketFactory";
        InetSocketAddress remote(ifaces.GetAddress(p.to), p.port);

        // ---- Q16 / Q17: sink on the receiver, source on the sender --------
        PacketSinkHelper sinkHelper(factory, InetSocketAddress(Ipv4Address::GetAny(), p.port));
        ApplicationContainer sinkApp = sinkHelper.Install(nodes.Get(p.to));
        sinkApp.Start(Seconds(0.0));
        sinkApp.Stop(Seconds(simTime));
        sinks.Add(sinkApp);

        ApplicationContainer srcApp;
        if (p.tcp)
        {
            BulkSendHelper bulk(factory, remote);
            bulk.SetAttribute("MaxBytes", UintegerValue(0));  // send until stopped
            srcApp = bulk.Install(nodes.Get(p.from));
        }
        else
        {
            OnOffHelper onoff(factory, remote);
            onoff.SetConstantRate(DataRate(udpRate), 1000);
            srcApp = onoff.Install(nodes.Get(p.from));
        }
        srcApp.Start(Seconds(1.0));
        srcApp.Stop(Seconds(simTime));

        // ---- Q18: one trace file per sink ----------------------------------
        streams.push_back(ascii.CreateFileStream(p.name + "-bytes.txt"));
    }

    Simulator::Schedule(Seconds(0.0), &SampleBytes, sinks, streams);

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // ---- report ---------------------------------------------------------
    double active = simTime - 1.0;
    for (uint32_t i = 0; i < pairs.size(); ++i)
    {
        Ptr<PacketSink> sink = DynamicCast<PacketSink>(sinks.Get(i));
        std::cout << pairs[i].name << " n" << pairs[i].from << "->n" << pairs[i].to << " port "
                  << pairs[i].port << " : " << sink->GetTotalRx() << " bytes, "
                  << sink->GetTotalRx() * 8.0 / active / 1000.0 << " kbit/s" << std::endl;
    }

    Simulator::Destroy();
    return 0;
}
