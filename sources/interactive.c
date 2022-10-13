#include "../includes/ft_malcom.h"

static void print_if_info(char *selected_if)
{
	t_sockaddr_in ipv4, nm;
	t_sockaddr_ll mac;
	char *ipstr = NULL;
	uint8_t netmask = 0;

	get_if_addr((t_sockaddr *)&ipv4, selected_if, AF_INET);
	get_if_addr((t_sockaddr *)&mac, selected_if, AF_PACKET);
	get_if_netmask((t_sockaddr *)&nm, selected_if, AF_INET);

	print_box(30, 5, 26, 10);

	if (!ipv4.sin_addr.s_addr)
		ipstr = ft_strdup("\e[3;31mUnavailable\e[0m");
	else
	{
		ipstr = inet_ntoa(ipv4.sin_addr);
		netmask = get_decimal_netmask(nm.sin_addr.s_addr);
	}

	char *macstr = pkttos(mac.sll_addr);

	printf("\e[12;30H\e[1mIP:\e[0m %s/%u", ipstr, netmask);
	printf("\e[13;30H\e[1mMAC:\e[0m %s", macstr);
	free(macstr);
}

static char *if_selection(void)
{
	t_menu menu;
	char *selected_if = NULL;
	char **ifs = get_ifs_names();

	menu.selection_idx = 0;
	menu.alignement = 'v';
	menu.title = ft_strdup("Choose a network interface: ");

	create_menu(&menu, ifs);
	selected_if = display_menu(&menu, &print_if_info);

	ft_free_tab(ifs);
	destroy_menu(&menu);
	
	return (selected_if);
}

static char *ip_selection(t_sockaddr_in **ips, char *step_title)
{
	t_menu menu;
	char *selected_ip = NULL;
	char **tab = ft_add_tab_elem(NULL, NULL);

	for (int i = 0; ips[i] != NULL; i++)
		tab = ft_add_tab_elem(tab, inet_ntoa(ips[i]->sin_addr));

	menu.selection_idx = 0;
	menu.alignement = 'v';
	menu.title = ft_strdup(step_title);

	create_menu(&menu, tab);
	selected_ip = display_menu(&menu, &on_selection_no_op);

	ft_free_tab(tab);
	destroy_menu(&menu);

	return (selected_ip);
}

void ip_scan_loading(uint32_t counter, uint32_t total)
{
	(void)counter, (void)total;

	uint8_t percent = (uint8_t)((double)counter / (double)total * 100.0);
	display_loading_bar(0, 20, percent, "Scanning IPs :");
}

void interactive(t_malcom *mstruct)
{
	START_IHM_CONTEXT();
	char *selected_if = if_selection();

	t_sockaddr_in ip_nm, ip_broad, ip_last, ip_first;

	ft_bzero(&ip_last, sizeof(t_sockaddr_in));
	get_if_netmask((t_sockaddr *)&ip_nm, selected_if, AF_INET);
	get_if_brd((t_sockaddr *)&ip_broad, selected_if, AF_INET);
	ip_last.sin_family = AF_INET;
	ip_first.sin_family = AF_INET;
	ip_last.sin_addr.s_addr = ip_get_last_ip(ip_broad.sin_addr.s_addr, ip_nm.sin_addr.s_addr);
	ip_first.sin_addr.s_addr = ip_get_net(ip_broad.sin_addr.s_addr, ip_nm.sin_addr.s_addr);

	t_sockaddr_in **ips = getavailableips(&ip_first, &ip_last, &ip_first, &ip_broad, &ip_scan_loading);
	char *target_ip = ip_selection(ips, "Choose a target to attack:");
	char *spoofed_ip = ip_selection(ips, "Choose an IP to spoof:");
	freeavailableips(ips);
	END_IHM_CONTEXT();

	printf("Performing an ARP flooding attack on %s. Spoofed IP is %s\n", spoofed_ip, target_ip);

	char *_argv[6] = {"", "-v", "-f", spoofed_ip, target_ip, NULL};

	char **argv = ft_copy_tab(_argv);

	mstruct->mode = 0;

	parse(5, argv, mstruct);
	create_arp_socket(mstruct);

	arp_flooding(mstruct);
	ft_free_tab(argv);
	free(selected_if);
	free(target_ip);
	free(spoofed_ip);
}