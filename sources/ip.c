#include "../includes/ft_malcom.h"

in_addr_t ip_get_net(in_addr_t ipv4, in_addr_t netmask)
{
	return ((in_addr_t)(ipv4 & netmask));
}

uint32_t ip_to_int32(in_addr_t ip) {
	return (
		(ip >> 24 & 0x000000ff) | (ip >> 8 & 0x0000ff00) |
		(ip << 8 & 0x00ff0000) | (ip << 24 & 0xff000000)
	);
}

uint8_t	is_ip_in_subnet(in_addr_t ipv4, in_addr_t netaddr, in_addr_t broadcast)
{
	if (ip_to_int32(ipv4) >= ip_to_int32(netaddr) && ip_to_int32(ipv4) <= ip_to_int32(broadcast)){
		return (TRUE);
	}
	return (FALSE);
}