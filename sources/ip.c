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

in_addr_t ip_get_last_ip(in_addr_t ip, in_addr_t netmask)
{
	in_addr_t netip = ip_get_net(ip, netmask);
	return (netip | (~netmask));
}

uint8_t get_decimal_netmask(in_addr_t netmask)
{
	uint32_t ip_le = ip_to_int32(netmask);

	for (uint8_t i = 0; i < 32; i++){
		if (!(((uint8_t)(~ip_le >> i)) & 0b00000001))
			return (32-i);
	}

	return (32);
}