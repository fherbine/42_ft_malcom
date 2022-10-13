#include "../includes/ft_malcom.h"

void message_exit(char *msg, int status)
{
	dprintf((status == EXIT_FAILURE) ? STDERR : STDOUT, "ft_malcom: %s\n", msg);
	exit(status);
}

void invalid_host_ip(char *host)
{
	dprintf(STDERR, "ft_malcom: unknown host or invalid IP address: (%s).\n", host);
	exit(EXIT_FAILURE);
}

void invalid_mac_addr(char *mac)
{
	dprintf(STDERR, "ft_malcom: invalid MAC address: (%s).\n", mac);
}

void display_usage(uint8_t w_exit)
{
	printf("Usage:\n");
	printf("sudo ./ft_malcom [ -h -v ] [-I ] | [-p [-R] <spoofed IP / hostname> <spoofed MAC addr> \
<target IP / hostname> <target MAC>] | [-f [-i interval] <spoofed IP / hostname> \
<target IP / hostname>]\n");
	printf(" -h\tDisplay usage & exit.\n");
	printf(" -v\tEnable verbose mode.\n");
	printf(" -p\tPerform an ARP Poisoning attack.\n");
	printf(" -f\tPerform an ARP Flooding attack.\n");
	printf(" -I\tUse the interactive mode (using ARP flooding).\n");
	printf("\n");
	printf("Poisonning arguments:\n");
	printf(" spoofed host/IP\tSource IP address / hostname.\n");
	printf(" spoofed MAC\tSource MAC address.\n");
	printf(" dst host/IP\tTargetted IP address / hostname.\n");
	printf(" dst MAC\tTargetted MAC address.\n");
	printf("\n");
	printf("Poisonning options:\n");
	printf(" -R          \tSend an ARP REQUEST back after a delay to ensure cache poisonning.\n");
	printf("\n");
	printf("Flooding arguments:\n");
	printf(" spoofed host/IP\tSource IP address / hostname.\n");
	printf(" dst host/IP\tTargetted IP address / hostname.\n");
	printf("\n");
	printf("Flooding options:\n");
	printf(" -i <interval>\tCustom flooding interval (default 5 secs).\n");

	if (w_exit)
		exit(EXIT_FAILURE);
}

void invalid_option(char *optn)
{
	printf("Invalid option -- '%s'\n", optn);
	display_usage(TRUE);
}

void ip_is_not_reachable(struct in_addr ipv4, char *host)
{
	dprintf(
		STDERR,
		"ft_malcom: %s (%s) is not locally reachable through your network interfaces.\n",
		host, inet_ntoa(ipv4)
	);
}

void not_in_the_same_net(char *host1, char *host2)
{
	dprintf(
		STDERR,
		"ft_malcom: %s is not in the same network as %s.\n",
		host1, host2
	);
}