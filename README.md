# ARP_spoofing
## First step of a man in the middle attack in a LAN
ft_malcolm [Options] <source_ip> <source_mac> <target_ip> <target_mac>  
Options:
* -c Number	stop after sending Number arp packets
* -i Number	wait Number second between sending each packet
* -d Device	listen and send arp request on Device
* -f		    flood the target
* -v		    show content of the arp packets send and receive
