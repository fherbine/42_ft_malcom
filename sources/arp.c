#include "../includes/ft_malcom.h"

void create_arp_socket(t_malcom *mstruct)
{
	if ((mstruct->socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
		perror("socket"); exit(EXIT_FAILURE);}
}

void send_arp(uint8_t arp_opcode, t_malcom *mstruct)
{
	char buffer[PACKET_SIZE];
	t_arp_pkt pkt;

	ft_bzero(&pkt, sizeof(t_arp_pkt));
	ft_bzero(buffer, PACKET_SIZE);

	ft_memcpy(pkt.eth_h.h_dest, mstruct->src_host.sock_addr_ll.sll_addr, ETH_ALEN);
	ft_memcpy(pkt.eth_h.h_source, mstruct->dst_host.sock_addr_ll.sll_addr, ETH_ALEN);
	pkt.eth_h.h_proto = htons(ETH_P_ARP);

	pkt.arp_h.ar_hrd = htons(ARPHRD_ETHER);
	pkt.arp_h.ar_pro = htons(ETH_P_IP);
	pkt.arp_h.ar_hln = ETH_ALEN;
	pkt.arp_h.ar_pln = IP_ALEN;
	pkt.arp_h.ar_op = htons(arp_opcode);

	ft_memcpy(pkt.ar_tha, mstruct->src_host.sock_addr_ll.sll_addr, ETH_ALEN);
	ft_memcpy(pkt.ar_sha, mstruct->dst_host.sock_addr_ll.sll_addr, ETH_ALEN);
	ft_memcpy(pkt.ar_tip, &(mstruct->src_host.sock_addr_in.sin_addr), IP_ALEN);
	ft_memcpy(pkt.ar_sip, &(mstruct->dst_host.sock_addr_in.sin_addr), IP_ALEN);

	ft_memcpy(buffer, &pkt, sizeof(t_arp_pkt));


	ssize_t ret = sendto(
		mstruct->socketfd, (void *)buffer, PACKET_SIZE, 0,
		(t_sockaddr *)&(mstruct->dst_host.sock_addr_ll), sizeof(t_sockaddr_ll)
	);
	if (ret < 0) {
		dprintf(STDERR, "An error occured when sending the packet.\n");
	}
	else if (mstruct->options.flags & MALC_OPT_VERBOSE)
		show_arp_pkt("\e[34;1;4mPacket sent:\e[0m\n", &pkt);
}

void	recv_arp(t_arp_pkt *pkt, t_malcom *mstruct)
{
	t_sockaddr_ll src_ha;
	socklen_t src_halen = 0;
	ft_bzero(pkt, sizeof(t_arp_pkt));

	ssize_t brecv = recvfrom(
		mstruct->socketfd, (void *)pkt, sizeof(t_arp_pkt), 0,
		(t_sockaddr *)&src_ha, &src_halen
	);

	if (brecv < 0)
		dprintf(STDERR, "An error occured during ARP reception.\n");
	else if (mstruct->options.flags & MALC_OPT_VERBOSE)
		show_arp_pkt("\e[35;1;4mPacket received:\e[0m\n", pkt);
}