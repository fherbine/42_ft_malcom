#ifndef MINI_NMAP_H
# define MINI_NMAP_H

# include "../libft/libft.h"

/* icmp, ip */
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>

/* send / recv */
# include <sys/types.h>
# include <sys/socket.h>

/* htons / ntohs */
# include <arpa/inet.h>

/* getpid */
# include <unistd.h>

/* timeval */
# include <sys/time.h>

# define PING_OK 1
# define PING_KO -1
# define PING_TMEO 0.1

typedef struct icmphdr t_icmphdr;
typedef struct ip t_ip;
typedef struct iphdr t_iphdr;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_in6 t_sockaddr_in6;
typedef struct sockaddr t_sockaddr;

/* icmp.c */
void	send_icmp(int socketfd, in_addr_t target);
uint8_t receive_icmp(int socketfd, t_sockaddr_in *addr);

/* mini_nmap.c */
t_sockaddr_in	**getavailableips(t_sockaddr_in *from, t_sockaddr_in *to, t_sockaddr_in *net, t_sockaddr_in *broad, void(*cb)(uint32_t, uint32_t));
void			freeavailableips(t_sockaddr_in **ips);

#endif