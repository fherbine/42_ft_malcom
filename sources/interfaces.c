#include "../includes/ft_malcom.h"

uint8_t	is_mac_in_ifs(uint8_t *macaddr)
{
	t_ifaddrs *ifs = NULL, *p = NULL;
	uint8_t ret = 0;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == AF_PACKET) {
			t_sockaddr_ll *sa_ll = (t_sockaddr_ll *)p->ifa_addr;
			
			if (!maccmp(macaddr, sa_ll->sll_addr)) {
				ret = sa_ll->sll_ifindex;
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
	return (ret);
}

char *is_ip_reachable(struct in_addr ip)
{
	t_ifaddrs *ifs = NULL, *p = NULL;
	char *ret = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == AF_INET) {
			in_addr_t if_ip = ((t_sockaddr_in *)p->ifa_addr)->sin_addr.s_addr;
			in_addr_t if_ipbrd = ((t_sockaddr_in *)p->ifa_broadaddr)->sin_addr.s_addr;
			in_addr_t if_netmask = ((t_sockaddr_in *)p->ifa_netmask)->sin_addr.s_addr;
			in_addr_t if_ipnet = ip_get_net(if_ip, if_netmask);
			
			if (is_ip_in_subnet(ip.s_addr, if_ipnet, if_ipbrd)) {
				ret = ft_strdup(p->ifa_name);
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
	return (ret);
}