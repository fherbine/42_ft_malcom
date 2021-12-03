#include "../includes/ft_malcom.h"

void show_arp_pkt(char *label, t_arp_pkt *pkt)
{
	char opcode_map[10][4] = {
		"REQ\0", "REP\0", "RRQ\0", "RRP\0", "", "", "", "IRQ\0", "IRP\0", "NAK\0"
	};
	struct in_addr ips, ipd;
	ips.s_addr = *((in_addr_t *)pkt->ar_sip);
	ipd.s_addr = *((in_addr_t *)pkt->ar_tip);

	printf("%s", label);
	printf("\e[0;1mARP opcode:\e[0m %s (%x)\n", opcode_map[ntohs(pkt->arp_h.ar_op)-1], ntohs(pkt->arp_h.ar_op)); 
	printf("\e[0;1mIP src:\e[0m %s\n", inet_ntoa(ips));
	printf("\e[0;1mMAC src:\e[0m %s\n", pkttos(pkt->ar_sha));
	printf("\e[0;1mIP dst:\e[0m %s\n", inet_ntoa(ipd));
	printf("\e[0;1mMAC dst:\e[0m %s\n", pkttos(pkt->ar_tha));
}