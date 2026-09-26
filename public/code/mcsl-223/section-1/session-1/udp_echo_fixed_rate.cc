/*
 * MCSL-223 Section 1, Session 1, Question 2
 * UDP echo client and server on the two-node link, sending at a fixed rate.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/udp_echo_fixed_rate
 *
 * Fixed data rate: packet size L = 1024 bytes, rate R = 1 Mbit/s,
 * so the client interval is 8L/R = 8192 / 1e6 = 8.192 ms.
 *
 *   n0 (client) ---------- n1 (server, port 9)
 *   10.1.1.1   5 Mbps, 2 ms   10.1.1.2
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UdpEchoFixedRate");

/*
 * main: builds the Session 1 link, puts a UdpEchoServer on n1 and a
 * UdpEchoClient on n0 that sends maxPackets packets of packetSize bytes
 * every 8*packetSize/rate seconds, then runs for 10 s.
 */
int
main(int argc, char* argv[])
{
    uint32_t packetSize = 1024;   // bytes
    uint32_t maxPackets = 10;
    double rateBps = 1e6;         // bit/s, the fixed data rate

    CommandLine cmd(__FILE__);
    cmd.AddValue("packetSize", "UDP payload in bytes", packetSize);
    cmd.AddValue("maxPackets", "Packets the client sends", maxPackets);
    cmd.AddValue("rate", "Client data rate in bit/s", rateBps);
    cmd.Parse(argc, argv);

    // Print the client and server log lines (the expected output).
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    NetDeviceContainer devices = p2p.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // Server on n1, listening on UDP port 9.
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    // Client on n0. Interval = 8L/R seconds gives the fixed rate.
    double intervalUs = 8.0 * packetSize / rateBps * 1e6;
    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(maxPackets));
    echoClient.SetAttribute("Interval", TimeValue(MicroSeconds(static_cast<uint64_t>(intervalUs))));
    echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));
    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    std::cout << "Client rate " << rateBps / 1e6 << " Mbit/s, packet " << packetSize
              << " B, interval " << intervalUs / 1000.0 << " ms, packets " << maxPackets
              << std::endl;

    p2p.EnablePcapAll("session1-echo");

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
