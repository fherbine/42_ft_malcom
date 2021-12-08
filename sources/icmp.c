#include "../includes/mini_nmap.h"

static uint16_t compile_checksum(void *addr, ssize_t count)
{
	/* Inspired by RFC1141 */
	uint32_t sum = 0;

	while( count > 1 )  {
		/*  This is the inner loop */
			sum += *(uint16_t *)(addr);
			addr += 2;
			count -= 2;
	}

		/*  Add left-over byte, if any */
	if( count > 0 )
			sum += *(uint8_t *)addr;

		/*  Fold 32-bit sum to 16 bits */
	while (sum>>16)
		sum = (sum & 0xffff) + (sum >> 16);

	return(~sum);
}

void send_icmp(int socketfd, in_addr_t target)
{
	t_icmphdr icmp_hdr;
	t_sockaddr_in ip_dst;

	ft_bzero(&icmp_hdr, sizeof(t_icmphdr));
	ft_bzero(&ip_dst, sizeof(t_sockaddr_in));

	ip_dst.sin_addr.s_addr = target;
	ip_dst.sin_family = AF_INET;

	icmp_hdr.type = ICMP_ECHO;
	icmp_hdr.un.echo.id = (uint16_t)getpid();
	icmp_hdr.checksum = compile_checksum(&icmp_hdr, sizeof(t_icmphdr));

	if (sendto(
		socketfd, &icmp_hdr, sizeof(t_icmphdr), 0,
		(t_sockaddr *)&ip_dst, sizeof(t_sockaddr_in)
	) <= 0)
		exit(EXIT_FAILURE);
}

uint8_t receive_icmp(int socketfd, t_sockaddr_in *addr)
{
	char *recvbuffer[1024];
	socklen_t addrlen = sizeof(t_sockaddr_in);

	ft_bzero(recvbuffer, 1024);
	ft_bzero(addr, sizeof(addr));

	if (recvfrom(socketfd, (void *)recvbuffer, 1023, MSG_WAITALL, (t_sockaddr *)addr, &addrlen) <= 0)
		return (PING_KO);

	t_icmphdr *icmp_hdr = (void *)recvbuffer + sizeof(t_iphdr);

	if (icmp_hdr->type == ICMP_ECHOREPLY) {
		return (PING_OK);
	}
	
	return (PING_KO);
}