#include "../includes/mitm.h"

void			print_arp(struct s_arphdr *arp)
{
	char	ipstr[INET_ADDRSTRLEN];

	printf("\n##Address Resolution Protocol##\n");
	printf("Hardware type: Ethernet (%d)\n", ntohs(arp->hrd));
	printf("Protocal type: IPV4 (%d)\n", ntohs(arp->pro));
	printf("Hardware size: %d\n", arp->hlen);
	printf("Protocol size: %d\n", arp->plen);
	printf("Opcode: %s (%d)\n", ntohs(arp->op) == ARPOP_REQUEST ? "request" : "reply", ntohs(arp->op));
	printf("Sender MAC address: %x:%x:%x:%x:%x:%x\n", arp->sha[0], arp->sha[1], arp->sha[2], arp->sha[3]
		, arp->sha[4], arp->sha[5]);
	inet_ntop(AF_INET, arp->spa, ipstr, INET_ADDRSTRLEN);
	printf("Sender IP address: %s\n", ipstr);
	printf("Target MAC address: %x:%x:%x:%x:%x:%x\n", arp->dha[0], arp->dha[1], arp->dha[2], arp->dha[3]
		, arp->dha[4], arp->dha[5]);
	inet_ntop(AF_INET, arp->dpa, ipstr, INET_ADDRSTRLEN);
	printf("Target IP address: %s\n", ipstr);
}