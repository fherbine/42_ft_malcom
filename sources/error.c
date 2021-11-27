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

void display_usage(uint8_t w_exit)
{
	printf("Usage:\n");
	printf("sudo ./ft_malcom [ -h ] [-p <src IP / hostname> <src MAC addr> \
<target IP / hostname> <target MAC>] [-f [-i interval] <src IP / hostname> \
<target IP / hostname>]\n");
	printf(" -h\tDisplay usage & exit.\n");
	printf(" -p\tPerform an ARP Poisoning attack.\n");
	printf(" -f\tPerform an ARP Flooding attack.\n");
	printf("\n");
	printf("Poisonning arguments:\n");
	printf(" src host/IP\tSource IP address / hostname.\n");
	printf(" src MAC\tSource MAC address.\n");
	printf(" dst host/IP\tTargetted IP address / hostname.\n");
	printf(" dst MAC\tTargetted MAC address.\n");
	printf("\n");
	printf("Poisonning arguments:\n");
	printf(" src host/IP\tSource IP address / hostname.\n");
	printf(" dst host/IP\tTargetted IP address / hostname.\n");
	printf("\n");
	printf("Poisonning options:\n");
	printf(" -i <interval>\tCustom flooding interval (default 5 secs).\n");

	if (w_exit)
		exit(EXIT_FAILURE);
}

void invalid_option(char *optn)
{
	printf("Invalid opttion -- '%s'", optn);
	display_usage(TRUE);
}