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
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* inet_ntoa */
#include <arpa/inet.h>

/* typedefs */
typedef struct addrinfo t_addrinfo;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr_in6 t_sockaddr_in6;
typedef struct sockaddr t_sockaddr;
typedef t_sockaddr t_sockaddr_hw;

/* defines */
# define MALC_MODE_POISON 0x01
# define MALC_MODE_FLOOD 0x02

# define MALC_OPT_FLOOD_INVAL 0x01

/* conf */
# define FLOOD_INVAL 5

/* structures */
typedef struct		s_options {
	uint8_t			flags;
	void			*optn_data[256];
}					t_options;

typedef struct		s_host {
	t_sockaddr_hw	sock_addr_hw;
	t_sockaddr_in	sock_addr_in;
	char			*hostname;
	char			*macstr;
}					t_host;

typedef struct		s_malcom {
	uint8_t			mode;
	t_options		options;	
	t_host			src_host;
	t_host			dst_host;
}					t_malcom;

/* prototypes */

/** error.c **/
void 	message_exit(char *msg, int status);
void 	invalid_host_ip(char *host);
void	display_usage(uint8_t w_exit);
void 	invalid_option(char *optn);

/* parser.c */
void	parse(int argc, char **argv, t_malcom *mstruct);

/* main.c */
void	free_malcom_struct(t_malcom *mstruct);

/* debug.c */
void	display_mstruct(t_malcom *mstruct);

/* nslookup */
void	dnslookup(char *host, t_sockaddr *addr, uint8_t ipver);

#endif