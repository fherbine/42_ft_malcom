#ifndef FT_MALCOM_H
# define FT_MALCOM_H

/* includes */
/** libft **/
# include "../libft/libft.h"
/** printf **/
# include <stdio.h>

/** in_addr **/
# include <netinet/in.h>

/** socket related **/
# include <sys/types.h>
# include <sys/socket.h>

/* getaddrinfo */
# include <sys/socket.h>
# include <netdb.h>

/* inet_ntoa */
# include <arpa/inet.h>

/* getifaddrs, freeifaddrs */
# include <ifaddrs.h>

/* eth struct */
# include <linux/if_packet.h>
# include <linux/if_ether.h>
# include <linux/if_arp.h>

/* typedefs */
typedef struct addrinfo t_addrinfo;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_in6 t_sockaddr_in6;
typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_ll t_sockaddr_ll;
typedef struct ifaddrs t_ifaddrs;
typedef struct ethhdr t_ethhdr;
typedef struct arphdr t_arphdr;

/* defines */
# define MALC_MODE_POISON 0x01
# define MALC_MODE_FLOOD 0x02

# define MALC_OPT_FLOOD_INVAL 0x01

/* conf */
# define FLOOD_INVAL 5

/* fixed values */
# define IP_ALEN 4
# define PACKET_SIZE 60

/* structures */
typedef struct		s_options {
	uint8_t			flags;
	void			*optn_data[256];
}					t_options;

typedef struct		s_host {
	t_sockaddr_ll	sock_addr_ll;
	t_sockaddr_in	sock_addr_in;
	char			*hostname;
	char			*macstr;
	char			*ifa_name;
}					t_host;

typedef struct		s_malcom {
	uint8_t			mode;
	t_options		options;	
	t_host			src_host;
	t_host			dst_host;
	int				socketfd;
}					t_malcom;

typedef struct		s_arp_pkt {
	t_ethhdr		eth_h;
	t_arphdr		arp_h;
	unsigned char	ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char	ar_sip[IP_ALEN];	/* sender IP address		*/
	unsigned char	ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char	ar_tip[IP_ALEN];	/* target IP address		*/
}					t_arp_pkt;

/* prototypes */

/** error.c **/
void 	message_exit(char *msg, int status);
void 	invalid_host_ip(char *host);
void	invalid_mac_addr(char *mac);
void	display_usage(uint8_t w_exit);
void 	invalid_option(char *optn);
void 	ip_is_not_reachable(struct in_addr ipv4, char *host);
void 	not_in_the_same_net(char *host1, char *host2);

/* parser.c */
void	parse(int argc, char **argv, t_malcom *mstruct);

/* main.c */
void	free_malcom_struct(t_malcom *mstruct);

/* debug.c */
void		display_mstruct(t_malcom *mstruct);
void 		print_buffer(void *buffer_addr, ssize_t len);

/* nslookup */
void		dnslookup(char *host, t_sockaddr *addr, uint8_t ipver);

/* mac.c */
int			stopkt(char *macstr, t_sockaddr_ll *sa_pkt, uint16_t eth_proto);
char		*pkttos(void *ha_addr);
int			maccmp(uint8_t *addr1, uint8_t *addr2);

/* interfaces.c */
uint8_t		is_mac_in_ifs(uint8_t *macaddr);
char		*is_ip_reachable(struct in_addr ip);

/* ip.c */
in_addr_t	ip_get_net(in_addr_t ipv4, in_addr_t netmask);
uint8_t		is_ip_in_subnet(in_addr_t ipv4, in_addr_t netaddr, in_addr_t broadcast);

/* arp.c */
void		create_arp_socket(t_malcom *mstruct);
void		send_arp(uint8_t arp_opcode, t_malcom *mstruct);
void		recv_arp(t_arp_pkt *pkt, t_malcom *mstruct);

#endif