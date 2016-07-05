
Assignment no.:2(group A)
Title:-A fire is to be detected using relevant wireless sensor network installed in a remote location
to communicate the data to the central server for the monitoring purpose and detection of
the fire. Write a program to implement the system using WSN and Different data
communication strategies/ algorithms (at least two) to compare the reliability of the data
received and efficient timing. Use of Fort Forwarding/Tunneling Protocol is expected.
Batch:T3                                                                                                                                                      

----------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/animation-interface.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/aodv-helper.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include <ns3/lr-wpan-module.h>
#include "ns3/energy-module.h"
using namespace ns3;
using namespace std;
class SenseApp : public Application
{
public:
    SenseApp ();
    virtual ~SenseApp();
    void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);
    void SetThersold(uint32_t tmp);
private:
    virtual void StartApplication (void);
    virtual void StopApplication (void);
    void ScheduleTx (void);
    void SendPacket (void);

    Ptr<Socket> m_socket;
    Address m_peer;
    uint32_t m_packetSize;
    uint32_t m_nPackets;
    DataRate m_dataRate;
    EventId m_sendEvent;
    bool m_running;
    uint32_t m_packetsSent;
    uint32_t m_temp;
    Ptr<UniformRandomVariable> m_uniformRandomVariable;
};


SenseApp::SenseApp (): m_socket (0),m_peer (),m_packetSize (0),m_nPackets (0),m_dataRate (0),m_sendEvent (),m_running (false),m_packetsSent (0)
{
m_uniformRandomVariable = CreateObject<UniformRandomVariable> ();
m_temp=40;
}

SenseApp::~SenseApp()
{
m_socket = 0;
}

void SenseApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
m_socket = socket;
m_peer = address;
m_packetSize = packetSize;
m_nPackets = nPackets;
m_dataRate = dataRate;
}

void SenseApp::StartApplication (void)
{
m_running = true;
m_packetsSent = 0;
m_socket->Bind ();
m_socket->Connect (m_peer);
SendPacket ();
}

void SenseApp::SetThersold(uint32_t tmp)
{
m_temp=tmp;
}
void SenseApp::StopApplication (void)
{
m_running = false;

    if (m_sendEvent.IsRunning ())
    {
    Simulator::Cancel (m_sendEvent);
    }
    if (m_socket)
    {
    m_socket->Close ();
    }
}
void SenseApp::SendPacket (void)
{
uint32_t temp=m_uniformRandomVariable->GetInteger (0, 50);
NS_LOG_UNCOND("Node "<<m_node->GetId()<<" Sense the Temperature value is \t"<<temp);
if(temp>m_temp){
Ptr<Packet> packet = Create<Packet> (m_packetSize);
m_socket->Send (packet);
NS_LOG_UNCOND("Node"<<m_node->GetId()<<" Sent one packet to Sink");
}
if (++m_packetsSent < m_nPackets)
    {
    ScheduleTx ();
    }
}
void SenseApp::ScheduleTx (void)
{
    if (m_running)
    {
    Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
    m_sendEvent = Simulator::Schedule (tNext, &SenseApp::SendPacket,this);
    }
}
int main(int argc, char** argv) 
{
    NS_LOG_COMPONENT_DEFINE ("WifiAdhoc_Routing");
    std::string phyMode ("DsssRate1Mbps");
    uint16_t num_node = 5;
    NodeContainer node;
    node.Create (num_node);

    MobilityHelper mobility;
    mobility.SetPositionAllocator ("ns3::GridPositionAllocator","MinX",DoubleValue (0.0),"MinY", DoubleValue (0.0),"DeltaX", DoubleValue(10.0), "DeltaY", DoubleValue (10.0),"GridWidth", UintegerValue (10),"LayoutType", StringValue ("RowFirst"));
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (node);
    WifiHelper wifi;
    YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
    wifiPhy.Set ("RxGain", DoubleValue (-12) );
    wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
    YansWifiChannelHelper wifiChannel;
    wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
    wifiChannel.AddPropagationLoss("ns3::FriisPropagationLossModel");
    wifiPhy.SetChannel (wifiChannel.Create ());
    NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
    wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager","DataMode",StringValue(phyMode), "ControlMode",StringValue (phyMode));
    wifiMac.SetType ("ns3::AdhocWifiMac");
    NetDeviceContainer Devices;
    Devices = wifi.Install (wifiPhy, wifiMac, node);
    AsciiTraceHelper ascii;
    wifiPhy.EnableAsciiAll (ascii.CreateFileStream ("out.tr"));
    wifiPhy.EnablePcap ("out", Devices);
    AodvHelper aodv;
    Ipv4StaticRoutingHelper staticRouting;
    Ipv4ListRoutingHelper list;
    list.Add (staticRouting, 0);
    list.Add (aodv, 10);
    InternetStackHelper internet;
    internet.SetRoutingHelper (list);
    internet.Install (node);
    Ipv4AddressHelper ipv4;
    ipv4.SetBase ("192.168.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i;
    i = ipv4.Assign (Devices);
    uint16_t sinkPort = 4000;
    Address sinkAddress (InetSocketAddress (i.GetAddress (0),sinkPort));
    PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory",InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
    ApplicationContainer sinkApps = packetSinkHelper.Install (node.Get(0));
    sinkApps.Start (Seconds (0.));
    sinkApps.Stop (Seconds (20.));
    Ptr<SenseApp> app[100];
    Ptr<Socket> ns3UdpSocket[100];
    for (int i=0;i<num_node;i++)
    {
    ns3UdpSocket[i] = Socket::CreateSocket (node.Get (i),UdpSocketFactory::GetTypeId ());
    app[i]= CreateObject<SenseApp> ();
    app[i]->Setup (ns3UdpSocket[i], sinkAddress, 64, 10000, DataRate("1Mbps"));
    app[i]->SetThersold(30);
    node.Get (i)->AddApplication (app[i]);
    app[i]->SetStartTime (Seconds (1.));
    app[i]->SetStopTime (Seconds (20.));
    }
    Simulator::Run();
    Simulator::Destroy();
    return 0;

} 



============OUTPUT==============================================
ccl@ccl-OptiPlex-3010:~$ cd workspace
ccl@ccl-OptiPlex-3010:~/workspace$ ls
Ass4.cc  ns-allinone-3.21  ns-allinone-3.21.tar.bz2
ccl@ccl-OptiPlex-3010:~/workspace$ cd ns-allinone-3.21
ccl@ccl-OptiPlex-3010:~/workspace/ns-allinone-3.21$ ls
bake      constants.py   netanim-3.105  pybindgen-0.17.0.876  util.py
build.py  constants.pyc  ns-3.21        README                util.pyc
ccl@ccl-OptiPlex-3010:~/workspace/ns-allinone-3.21$ cd ns-3.21
ccl@ccl-OptiPlex-3010:~/workspace/ns-allinone-3.21/ns-3.21$ ./waf --run scratch/Ass4


Node 0 Sense the Temperature value is 	41
Node0 Sent one packet to Sink
Node 1 Sense the Temperature value is 	47
Node1 Sent one packet to Sink
Node 2 Sense the Temperature value is 	10
Node 3 Sense the Temperature value is 	4
Node 4 Sense the Temperature value is 	14
Node 0 Sense the Temperature value is 	21
Node 1 Sense the Temperature value is 	18
Node 2 Sense the Temperature value is 	39
Node2 Sent one packet to Sink
Node 3 Sense the Temperature value is 	27
Node 4 Sense the Temperature value is 	8
Node 0 Sense the Temperature value is 	21
Node 1 Sense the Temperature value is 	43
Node1 Sent one packet to Sink
Node 2 Sense the Temperature value is 	34
Node2 Sent one packet to Sink
Node 3 Sense the Temperature value is 	4
Node 4 Sense the Temperature value is 	50
Node4 Sent one packet to Sink
Node 0 Sense the Temperature value is 	5
Node 1 Sense the Temperature value is 	48
Node1 Sent one packet to Sink
Node 2 Sense the Temperature value is 	10
Node 3 Sense the Temperature value is 	48
Node3 Sent one packet to Sink
Node 4 Sense the Temperature value is 	15
Node 0 Sense the Temperature value is 	48
Node0 Sent one packet to Sink
Node 1 Sense the Temperature value is 	12
Node 2 Sense the Temperature value is 	0
Node 3 Sense the Temperature value is 	17
Node 4 Sense the Temperature value is 	33
Node4 Sent one packet to Sink
Node 0 Sense the Temperature value is 	37
Node0 Sent one packet to Sink
Node 1 Sense the Temperature value is 	19
Node 2 Sense the Temperature value is 	9
Node 3 Sense the Temperature value is 	47
Node3 Sent one packet to Sink
Node 4 Sense the Temperature value is 	39
Node4 Sent one packet to Sink
Node 0 Sense the Temperature value is 	23
Node 1 Sense the Temperature value is 	43
Node1 Sent one packet to Sink
Node 2 Sense the Temperature value is 	46
Node2 Sent one packet to Sink
Node 3 Sense the Temperature value is 	0
Node 4 Sense the Temperature value is 	42
Node4 Sent one packet to Sink
Node 0 Sense the Temperature value is 	29
Node 1 Sense the Temperature value is 	47
Node1 Sent one packet to Sink
Node 2 Sense the Temperature value is 	30
Node 3 Sense the Temperature value is 	34
Node3 Sent one packet to Sink
Node 4 Sense the Temperature value is 	35
Node4 Sent one packet to Sink
Node 0 Sense the Temperature value is 	22
Node 1 Sense the Temperature value is 	28
Node 2 Sense the Temperature value is 	20
Node 3 Sense the Temperature value is 	17
Node 4 Sense the Temperature value is 	21
Node 0 Sense the Temperature value is 	23
Node 1 Sense the Temperature value is 	1
Node 2 Sense the Temperature value is 	37
Node2 Sent one packet to Sink
Node 3 Sense the Temperature value is 	31
Node3 Sent one packet to Sink
^Z
[1]+  Stopped                 ./waf --run scratch/Ass4
ccl@ccl-OptiPlex-3010:~/workspace/ns-allinone-3.21/ns-3.21$ 


