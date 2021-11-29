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