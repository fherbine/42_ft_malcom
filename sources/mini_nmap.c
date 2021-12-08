#include "../includes/ft_malcom.h"

static void set_timeout(int *socketfd, double timeout_value) {
	struct timeval timeout;      
    timeout.tv_sec = (int) timeout_value;
    timeout.tv_usec = (int)(timeout_value * 100000);

	if (setsockopt(*socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		exit(EXIT_FAILURE);
}

t_sockaddr_in **getavailableips(t_sockaddr_in *from, t_sockaddr_in *to, t_sockaddr_in *net, t_sockaddr_in *broad, void(*cb)(uint32_t, uint32_t))
{
	uint32_t i = from->sin_addr.s_addr, i2 = 0;
	uint32_t len = htonl(to->sin_addr.s_addr) - htonl(i) - 1;
	t_sockaddr_in **tab = NULL;
	t_sockaddr_in ip_fetched;
	int socketfd;
	double timeout = PING_TMEO;

	if (!(tab = (t_sockaddr_in **)malloc(sizeof(t_sockaddr_in *) * len)))
		exit(EXIT_FAILURE);

	while (ntohl(i) <= ntohl(to->sin_addr.s_addr))
	{
		cb(len - ntohl(from->sin_addr.s_addr - i) + 1, len);
		if (i == broad->sin_addr.s_addr || i == net->sin_addr.s_addr)
		{
			i = htonl(htonl(i) + 1);
			continue ;
		}

		if ((socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
			dprintf(STDERR, "ft_malcom: You must be root to create RAW sockets !\n");
			exit(EXIT_FAILURE);
		}

		set_timeout(&socketfd, timeout);
		
		send_icmp(socketfd, i);
		ft_bzero(&ip_fetched, sizeof(t_sockaddr_in));
		ft_sleep(0.05);

		if (receive_icmp(socketfd, &ip_fetched) == PING_OK && ip_fetched.sin_addr.s_addr != 0) {
			t_sockaddr_in *ip = NULL;

			if (!(ip = (t_sockaddr_in *)malloc(sizeof(t_sockaddr_in))))
				exit(EXIT_FAILURE);
			
			ft_bzero(ip, sizeof(ip));
			ip->sin_family = AF_INET;
			ip->sin_addr.s_addr = i;
			tab[i2] = ip;
			i2++;
		}

		close(socketfd);
		i = htonl(htonl(i) + 1);
	}

	tab[i2] = NULL;
	
	return (tab);
}

void freeavailableips(t_sockaddr_in **ips)
{
	uint32_t i = 0;

	while (ips[i]) {
		free(ips[i]);
		i++;
	}
	free(ips);
}