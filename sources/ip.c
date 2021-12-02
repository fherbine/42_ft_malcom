#include "../includes/ft_malcom.h"

in_addr_t ip_get_net(in_addr_t ipv4, in_addr_t netmask)
{
	return ((in_addr_t)(ipv4 & netmask));
}

uint8_t	is_ip_in_subnet(in_addr_t ipv4, in_addr_t netaddr, in_addr_t broadcast)
{
	if (ipv4 >= netaddr && ipv4 <= broadcast)
		return (TRUE);
	return (FALSE);
}