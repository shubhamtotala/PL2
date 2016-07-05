TITLE:Write a program to Implement a packet sniffing tool in C++.
BATCH:
--------------------------------------------------------
#include <iostream>
#include <crafter.h>

/* Collapse namespaces */
using namespace std;
using namespace Crafter;

int main() {
        /* Set the interface */
        string iface = "wlan0";

        /* Get the IP address associated to the interface */
        string MyIP = GetMyIP(iface);
        cout << "[@] My IP address is  : " << MyIP  << endl;

        /* Create an IP header */
        IP ip_header;
        /* Set the Source and Destination IP address */
        ip_header.SetSourceIP("10.65.6.115");
        ip_header.SetDestinationIP("192.168.1.66");

        /* Create an TCP - SYN header */
        TCP tcp_header;
        tcp_header.SetSrcPort(11);
        tcp_header.SetDstPort(80);
        tcp_header.SetSeqNumber(RNG32());
        tcp_header.SetFlags(TCP::SYN);

        /* A raw layer, this could be any array of bytes or chars */
        RawLayer payload("GOOD AFTERNOON......");

        /* Create a packets */
        Packet tcp_packet = ip_header / tcp_header / payload;

        cout << endl << "[@] Print before sending: " << endl;
        tcp_packet.Print();

        /* Write the packet on the wire */
        tcp_packet.Send();

        cout << endl << "[@] Print after sending: " << endl;
        tcp_packet.Print();

        return 0;
}

---------------------------------------------------------------------
Output:-
ccl@ccl-OptiPlex-3020:~/Desktop$ g++ TCPpacket.cpp -o TCPpacket -lcrafter
ccl@ccl-OptiPlex-3020:~/Desktop$ sudo ./TCPpacket
[sudo] password for ccl: 
[@] My IP address is  : 192.168.1.108

[@] Print before sending: 
< IP (20 bytes) :: Version = 4 , HeaderLength = 5 , DiffServicesCP = 0 , ExpCongestionNot = 0 , TotalLength = 0 , Identification = 0x0 , Flags = 2 , FragmentOffset = 0 , TTL = 64 , Protocol = 0x6 , CheckSum = 0x0 , SourceIP = 10.65.6.115 , DestinationIP = 192.168.1.66 , >
< TCP (20 bytes) :: SrcPort = 11 , DstPort = 80 , SeqNumber = 3264811808 , AckNumber = 0 , DataOffset = 5 , Reserved = 0 , Flags = ( SYN ) , WindowsSize = 5840 , CheckSum = 0x0 , UrgPointer = 0 , >
< RawLayer (20 bytes) :: Payload = GOOD AFTERNOON......>

[@] Print after sending: 
< IP (20 bytes) :: Version = 4 , HeaderLength = 5 , DiffServicesCP = 0 , ExpCongestionNot = 0 , TotalLength = 60 , Identification = 0x0 , Flags = 2 , FragmentOffset = 0 , TTL = 64 , Protocol = 0x6 , CheckSum = 0x681e , SourceIP = 10.65.6.115 , DestinationIP = 192.168.1.66 , >
< TCP (20 bytes) :: SrcPort = 11 , DstPort = 80 , SeqNumber = 3264811808 , AckNumber = 0 , DataOffset = 5 , Reserved = 0 , Flags = ( SYN ) , WindowsSize = 5840 , CheckSum = 0x85a8 , UrgPointer = 0 , >
< RawLayer (20 bytes) :: Payload = GOOD AFTERNOON......>
ccl@ccl-OptiPlex-3020:~/Desktop$ 



