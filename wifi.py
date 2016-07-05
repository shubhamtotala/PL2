#!/usr/bin/env python
import sys
from scapy.all import *
count =0
k=0
found=0

Matrix = [[0 for x in xrange(6)] for x in xrange(6)]
def packet_handler(p):
     global Matrix
     global k
     global count
     global found
     if p.haslayer(Dot11) and p.type==0 and p.subtype==11:
          print(p.show())
          #check adress of AP
          if p.addr2 not in Matrix and p.addr2!="00:90:4c:91:00:03":
               Matrix[k][0]=str(p.addr2)
               Matrix[k][1]=1
               k=k+1
         
          for i in range(len(Matrix)):                 
                              
               if Matrix[i][0]==str(p.addr2):
                     Matrix[i][1]+=1
                     if Matrix[i][1]>3:
                          print "Authentication requests = "+ str(Matrix[i][1])+" Malicious user detected with MAC ID "+str(Matrix[i][0])
                          found=1                            
                          return
                    
              
                     #print "Address of the Client is ="+str(p.addr2)  
                    
          #count=count+1
          #print "This is packet number"+str(count)
          #print p.addr1
     #for i in range(len(Matrix)):
     #    print "Packet address "+str(Matrix[i][0])+" count is "+str(Matrix[i][1])
sniff(iface="mon0", prn=packet_handler)

'''OUTPUT

root@ubuntu:/home/hemlata# iwconfig
lo        no wireless extensions.

wlan0     IEEE 802.11bg  ESSID:"dd-wrt" 
          Mode:Managed  Frequency:2.437 GHz  Access Point: 00:90:4C:91:00:03  
          Bit Rate=11 Mb/s   Tx-Power=20 dBm  
          Retry  long limit:7   RTS thr:off   Fragment thr:off
          Encryption key:off
          Power Management:on
          Link Quality=70/70  Signal level=-38 dBm 
          Rx invalid nwid:0  Rx invalid crypt:0  Rx invalid frag:0
          Tx excessive retries:0  Invalid misc:61   Missed beacon:0

eth0      no wireless extensions.

root@ubuntu:/home/hemlata#

root@ubuntu:/home/hemlata# iw dev wlan0 interface add mon0 type monitor
root@ubuntu:/home/hemlata# iwconfig
lo        no wireless extensions.

mon0      IEEE 802.11bg  Mode:Monitor  Tx-Power=20 dBm  
          Retry  long limit:7   RTS thr:off   Fragment thr:off
          Power Management:on
         
wlan0     IEEE 802.11bg  ESSID:"dd-wrt" 
          Mode:Managed  Frequency:2.437 GHz  Access Point: 00:90:4C:91:00:03  
          Bit Rate=54 Mb/s   Tx-Power=20 dBm  
          Retry  long limit:7   RTS thr:off   Fragment thr:off
          Encryption key:off
          Power Management:on
          Link Quality=70/70  Signal level=-40 dBm 
          Rx invalid nwid:0  Rx invalid crypt:0  Rx invalid frag:0
          Tx excessive retries:0  Invalid misc:63   Missed beacon:0

eth0      no wireless extensions.


root@ubuntu:/home/hemlata# ifconfig mon0 up
root@ubuntu:/home/hemlata# iwconfig
lo        no wireless extensions.

mon0      IEEE 802.11bg  Mode:Monitor  Tx-Power=20 dBm  
          Retry  long limit:7   RTS thr:off   Fragment thr:off
          Power Management:on
         
wlan0     IEEE 802.11bg  ESSID:"dd-wrt" 
          Mode:Managed  Frequency:2.437 GHz  Access Point: 00:90:4C:91:00:03  
          Bit Rate=54 Mb/s   Tx-Power=20 dBm  
          Retry  long limit:7   RTS thr:off   Fragment thr:off
          Encryption key:off
          Power Management:on
          Link Quality=66/70  Signal level=-44 dBm 
          Rx invalid nwid:0  Rx invalid crypt:0  Rx invalid frag:0
          Tx excessive retries:0  Invalid misc:89   Missed beacon:0

eth0      no wireless extensions.

root@ubuntu:/home/hemlata#


root@ubuntu:/home/hemlata# python auth_sniff1.py
WARNING: No route found for IPv6 destination :: (no default route?)
###[ RadioTap dummy ]###
  version   = 0
  pad       = 0
  len       = 18
  present   = Flags+Rate+Channel+dBm_AntSignal+Antenna+b14
  notdecoded= '\x00\x02\x85\t\xa0\x00\xda\x01\x00\x00'
###[ 802.11 ]###
     subtype   = 11L
     type      = Management
     proto     = 0L
     FCfield   =
     ID        = 14849
     addr1     = 00:90:4c:91:00:03
     addr2     = 34:be:00:c6:1a:20
     addr3     = 00:90:4c:91:00:03
     SC        = 15792
     addr4     = None
###[ 802.11 Authentication ]###
        algo      = open
        seqnum    = 1
        status    = success
###[ 802.11 Information Element ]###
           ID        = vendor
           len       = 9
           info      = '\x00\x10\x18\x02\x00\x00\x04\x00\x00'
None
Address =34:be:00:c6:1a:20
###[ RadioTap dummy ]###
  version   = 0
  pad       = 0
  len       = 18
  present   = Flags+Rate+Channel+dBm_AntSignal+Antenna+b14
  notdecoded= '\x00\x02\x85\t\xa0\x00\xd0\x01\x00\x00'
###[ 802.11 ]###
     subtype   = 11L
     type      = Management
     proto     = 0L
     FCfield   =
     ID        = 14849
     addr1     = 34:be:00:c6:1a:20
     addr2     = 00:90:4c:91:00:03
     addr3     = 00:90:4c:91:00:03
     SC        = 2320
     addr4     = None
###[ 802.11 Authentication ]###
        algo      = open
        seqnum    = 2
        status    = success
###[ 802.11 Information Element ]###
           ID        = vendor
           len       = 9
           info      = '\x00\x10\x18\x02\x01\xf0\x00\x00\x00'
None
###[ RadioTap dummy ]###
  version   = 0
  pad       = 0
  len       = 18
  present   = Flags+Rate+Channel+dBm_AntSignal+Antenna+b14
  notdecoded= '\x00\x02\x85\t\xa0\x00\xde\x01\x00\x00'
###[ 802.11 ]###
     subtype   = 11L
     type      = Management
     proto     = 0L
     FCfield   =
     ID        = 14849
     addr1     = 00:90:4c:91:00:03
     addr2     = 34:be:00:c6:1a:20
     addr3     = 00:90:4c:91:00:03
     SC        = 16512
     addr4     = None
###[ 802.11 Authentication ]###
        algo      = open
        seqnum    = 1
        status    = success
###[ 802.11 Information Element ]###
           ID        = vendor
           len       = 9
           info      = '\x00\x10\x18\x02\x00\x00\x04\x00\x00'
None
Address =34:be:00:c6:1a:20
###[ RadioTap dummy ]###
  version   = 0
  pad       = 0
  len       = 18
  present   = Flags+Rate+Channel+dBm_AntSignal+Antenna+b14
  notdecoded= '\x00\x02\x85\t\xa0\x00\xd2\x01\x00\x00'
###[ 802.11 ]###
     subtype   = 11L
     type      = Management
     proto     = 0L
     FCfield   =
     ID        = 14849
     addr1     = 34:be:00:c6:1a:20
     addr2     = 00:90:4c:91:00:03
     addr3     = 00:90:4c:91:00:03
     SC        = 25392
     addr4     = None
###[ 802.11 Authentication ]###
        algo      = open
        seqnum    = 2
        status    = success
###[ 802.11 Information Element ]###
           ID        = vendor
           len       = 9
           info      = '\x00\x10\x18\x02\x01\xf0\x00\x00\x00'
None
###[ RadioTap dummy ]###
  version   = 0
  pad       = 0
  len       = 18
  present   = Flags+Rate+Channel+dBm_AntSignal+Antenna+b14
  notdecoded= '\x00\x02\x85\t\xa0\x00\xde\x01\x00\x00'
###[ 802.11 ]###
     subtype   = 11L
     type      = Management
     proto     = 0L
     FCfield   =
     ID        = 14849
     addr1     = 00:90:4c:91:00:03
     addr2     = 34:be:00:c6:1a:20
     addr3     = 00:90:4c:91:00:03
     SC        = 17520
     addr4     = None
###[ 802.11 Authentication ]###
        algo      = open
        seqnum    = 1
        status    = success
###[ 802.11 Information Element ]###
           ID        = vendor
           len       = 9
           info      = '\x00\x10\x18\x02\x00\x00\x04\x00\x00'
None
Address =34:be:00:c6:1a:20
Authentication requests = 4 Malicious user detected with MAC ID 34:be:00:c6:1a:20'''