#include "../includes/ft_malcom.h"

void show_arp_pkt(char *label, t_arp_pkt *pkt)
{
	char opcode_map[2][3] = {
		"REQ", "REP", "RRQ", "RRP", "", "", "", "IRQ", "IRP", "NAK"
	};
	struct in_addr ips, ipd;
	ips.s_addr = *((in_addr_t *)pkt->ar_sip);
	ipd.s_addr = *((in_addr_t *)pkt->ar_tip);

	printf("%s", label);
	printf("ARP received !\n");
	printf("ARP opcode: %s (%x)\n", opcode_map[ntohs(pkt->arp_h.ar_op)-1], ntohs(pkt->arp_h.ar_op)); 
	printf("IP src: %s\n", inet_ntoa(ips));
	printf("MAC src: %s\n", pkttos(pkt->ar_sha));
	printf("IP dst: %s\n", inet_ntoa(ipd));
	printf("MAC dst: %s\n", pkttos(pkt->ar_tha));
}