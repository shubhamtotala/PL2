#ASSIGNMENT NO.:  (group B)
#TITLE:Develop a GUI and write a Java/Pythn/C++ program to monitor Network Forensics,Investigating Logs and Investigating Network Traffic.
#Batch:T
----------------------------------------------------------------------
import socket, sys
from struct import *

#Convert a string of 6 characters of ethernet address into a dash separated hex string
def eth_addr (a) :
  b = "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" % (ord(a[0]) , ord(a[1]) , ord(a[2]), ord(a[3]), ord(a[4]) , ord(a[5]))
  return b

#create a AF_PACKET type raw socket (thats basically packet level)
#define ETH_P_ALL    0x0003          /* Every packet (be careful!!!) */
try:
	s = socket.socket( socket.AF_PACKET , socket.SOCK_RAW , socket.ntohs(0x0003))
except socket.error , msg:
	print 'Socket could not be created. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()

# receive a packet
while True:
	packet = s.recvfrom(65565)
	
	#packet string from tuple
	packet = packet[0]
	
	#parse ethernet header
	eth_length = 14
	
	eth_header = packet[:eth_length]
	eth = unpack('!6s6sH' , eth_header)
	eth_protocol = socket.ntohs(eth[2])
	print 'Destination MAC : ' + eth_addr(packet[0:6]) + ' Source MAC : ' + eth_addr(packet[6:12]) + ' Protocol : ' + str(eth_protocol)

	#Parse IP packets, IP Protocol number = 8
	if eth_protocol == 8 :
		#Parse IP header
		#take first 20 characters for the ip header
		ip_header = packet[eth_length:20+eth_length]
		
		#now unpack them :)
		iph = unpack('!BBHHHBBH4s4s' , ip_header)

		version_ihl = iph[0]
		version = version_ihl >> 4
		ihl = version_ihl & 0xF

		iph_length = ihl * 4

		ttl = iph[5]
		protocol = iph[6]
		s_addr = socket.inet_ntoa(iph[8]);
		d_addr = socket.inet_ntoa(iph[9]);

		print 'Version : ' + str(version) + ' IP Header Length : ' + str(ihl) + ' TTL : ' + str(ttl) + ' Protocol : ' + str(protocol) + ' Source Address : ' + str(s_addr) + ' Destination Address : ' + str(d_addr)

		
		#ICMP Packets
		if protocol == 1 :
			u = iph_length + eth_length
			icmph_length = 4
			icmp_header = packet[u:u+4]

			#now unpack them :)
			icmph = unpack('!BBH' , icmp_header)
			
			icmp_type = icmph[0]
			code = icmph[1]
			checksum = icmph[2]
			
			print 'Type : ' + str(icmp_type) + ' Code : ' + str(code) + ' Checksum : ' + str(checksum)
			
			h_size = eth_length + iph_length + icmph_length
			data_size = len(packet) - h_size
			
			#get data from the packet
			data = packet[h_size:]
			
			print 'Data : ' + data


#----------------------------------------------------------------------
OUTPUT:


Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 8
Version : 4 IP Header Length : 5 TTL : 64 Protocol : 6 Source Address : 10.65.6.115 Destination Address : 74.125.68.132
Destination MAC : b0:83:fe:8c:56:0c Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 8
Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 8
Version : 4 IP Header Length : 5 TTL : 64 Protocol : 6 Source Address : 10.65.6.115 Destination Address : 74.125.68.132
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 1544
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 1544
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 1544
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 1544
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 1544
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 1544
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 1544
Destination MAC : 2c:3e:cf:ff:2f:87 Source MAC : b0:83:fe:8c:56:0c Protocol : 1544
Destination MAC : b0:83:fe:8c:56:0c Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 8
Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : b0:83:fe:8c:56:0c Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 8
Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : b0:83:fe:8c:56:0c Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 8
Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : b0:83:fe:8c:56:0c Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 8
Version : 4 IP Header Length : 5 TTL : 63 Protocol : 6 Source Address : 74.125.68.132 Destination Address : 10.65.6.115
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : 2c:3e:cf:ff:2f:87 Protocol : 1544
Destination MAC : ff:ff:ff:ff:ff:ff Source MAC : a4:1f:72:77:a4:ac Protocol : 8
Version : 4 IP Header Length : 5 TTL : 128 Protocol : 17 Source Address : 10.65.6.176 Destination Address : 10.65.15.255

