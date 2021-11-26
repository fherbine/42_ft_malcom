#include "../includes/ft_malcom.h"

void message_exit(char *msg, int status)
{
	dprintf((status == EXIT_FAILURE) ? STDERR : STDOUT, "ft_malcom: %s\n", msg);
	exit(status);
}

void invalid_host_ip(char *host)
{
	dprintf(STDERR, "ft_malcom: unknown host or invalid IP address: (%s).", host);
	exit(EXIT_FAILURE);
}