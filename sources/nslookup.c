#include "../includes/ft_malcom.h"

void				dnslookup(char *host, t_sockaddr *addr, uint8_t ipver)
{
	t_addrinfo		hints;
	t_addrinfo		*first_info;

	ft_bzero(&hints, sizeof(t_addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;
	if (getaddrinfo(host, NULL, &hints, &first_info))
		invalid_host_ip(host);
	
	if (!first_info)
		exit(EXIT_FAILURE);

	t_addrinfo *p = NULL;

	p = first_info;
	while (p)
	{
		if (p->ai_family == ipver)
			ft_memcpy(addr, ((t_sockaddr *)p->ai_addr), sizeof(t_sockaddr_in));
		else if (p->ai_family == ipver)
			ft_memcpy(addr, ((t_sockaddr *)p->ai_addr), sizeof(t_sockaddr_in6));

		p = p->ai_next;
	}
	freeaddrinfo(first_info);
}