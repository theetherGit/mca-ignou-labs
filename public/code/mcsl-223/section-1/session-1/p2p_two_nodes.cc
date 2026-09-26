/*
 * MCSL-223 Section 1, Session 1, Question 1
 * Point-to-point topology with two nodes.
 *
 * Build: copy to ns-3.36+/scratch/ and run
 *   ./ns3 run scratch/p2p_two_nodes
 *
 * Topology:
 *   n0 ---------- n1
 *      5 Mbps, 2 ms
 *   10.1.1.1      10.1.1.2
 */
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("P2PTwoNodes");

/*
 * main: creates two nodes, joins them with one point-to-point link,
 * installs the IP stack, assigns 10.1.1.0/24 and prints what was built.
 * No traffic is sent; question 2 adds the applications.
 */
int
main(int argc, char* argv[])
{
    std::string dataRate = "5Mbps";
    std::string delay = "2ms";

    CommandLine cmd(__FILE__);
    cmd.AddValue("dataRate", "Link data rate", dataRate);
    cmd.AddValue("delay", "Link propagation delay", delay);
    cmd.Parse(argc, argv);

    // 1. Nodes: the two end hosts.
    NodeContainer nodes;
    nodes.Create(2);

    // 2. Channel and net devices: one full-duplex point-to-point link.
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue(dataRate));
    p2p.SetChannelAttribute("Delay", StringValue(delay));
    NetDeviceContainer devices = p2p.Install(nodes);

    // 3. Protocol stack: IPv4, UDP, TCP on both nodes.
    InternetStackHelper stack;
    stack.Install(nodes);

    // 4. Addresses: one /24 subnet for the link.
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // Report the topology so the lab record has something to show.
    std::cout << "Nodes created      : " << nodes.GetN() << std::endl;
    std::cout << "Link               : " << dataRate << ", delay " << delay << std::endl;
    for (uint32_t i = 0; i < nodes.GetN(); ++i)
    {
        std::cout << "n" << i << " address        : " << interfaces.GetAddress(i) << std::endl;
    }

    // Write a pcap per device (session1-0-0.pcap, session1-1-0.pcap).
    p2p.EnablePcapAll("session1");

    Simulator::Stop(Seconds(10.0));
    Simulator::Run();
    std::cout << "Simulation finished at " << Simulator::Now().GetSeconds() << " s" << std::endl;
    Simulator::Destroy();
    return 0;
}
