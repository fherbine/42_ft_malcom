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

void get_ip_from_ifname(in_addr_t *ipv4, char *ifname)
{
	t_ifaddrs *ifs = NULL, *p = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == AF_INET) {
			if (!ft_strcmp(ifname, p->ifa_name)) {
				*ipv4 = ((t_sockaddr_in *)p->ifa_addr)->sin_addr.s_addr;
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
}

void get_mac_from_ifname(t_sockaddr_ll *macaddr, char *ifname)
{
	t_ifaddrs *ifs = NULL, *p = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == AF_PACKET) {
			if (!ft_strcmp(ifname, p->ifa_name)) {
				ft_memcpy(macaddr, (t_sockaddr_ll *)p->ifa_addr, sizeof(t_sockaddr_ll));
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
}

void	get_if_brd(t_sockaddr *brd_addr, char *ifname, uint8_t sa_family)
{
	t_ifaddrs *ifs = NULL, *p = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == sa_family) {
			if (!ft_strcmp(ifname, p->ifa_name)) {
				size_t copy_size = 0;
				switch (sa_family)
				{
				case AF_INET:
					copy_size = sizeof(t_sockaddr_in);
					break;

				case AF_PACKET:
					copy_size = sizeof(t_sockaddr_ll);
					break;
				
				default:
					copy_size = sizeof(t_sockaddr);
					break;
				}
				ft_memcpy(brd_addr, p->ifa_broadaddr, copy_size);
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
}

char	**get_ifs_names(void)
{
	t_ifaddrs *ifs = NULL, *p = NULL;
	char **tab = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (!ft_is_in_tab(tab, p->ifa_name))
			tab = ft_add_tab_elem(tab, p->ifa_name);
		p = p->ifa_next;
	}
	freeifaddrs(ifs);
	return (tab);
}

void	get_if_addr(t_sockaddr *addr, char *ifname, uint8_t sa_family)
{
	t_ifaddrs *ifs = NULL, *p = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == sa_family) {
			if (!ft_strcmp(ifname, p->ifa_name)) {
				size_t copy_size = 0;
				switch (sa_family)
				{
				case AF_INET:
					copy_size = sizeof(t_sockaddr_in);
					break;

				case AF_PACKET:
					copy_size = sizeof(t_sockaddr_ll);
					break;
				
				default:
					copy_size = sizeof(t_sockaddr);
					break;
				}
				ft_memcpy(addr, p->ifa_addr, copy_size);
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
}

void	get_if_netmask(t_sockaddr *nm, char *ifname, uint8_t sa_family)
{
	t_ifaddrs *ifs = NULL, *p = NULL;

	if (getifaddrs(&ifs) < 0)
		exit(EXIT_FAILURE);

	p = ifs;

	while (p)
	{
		if (p->ifa_addr->sa_family == sa_family) {
			if (!ft_strcmp(ifname, p->ifa_name)) {
				size_t copy_size = 0;
				switch (sa_family)
				{
				case AF_INET:
					copy_size = sizeof(t_sockaddr_in);
					break;

				case AF_PACKET:
					copy_size = sizeof(t_sockaddr_ll);
					break;
				
				default:
					copy_size = sizeof(t_sockaddr);
					break;
				}
				ft_memcpy(nm, p->ifa_netmask, copy_size);
				break ;
			}
		}
		p = p->ifa_next;
	}
	
	freeifaddrs(ifs);
}
