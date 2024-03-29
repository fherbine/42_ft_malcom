#include "../includes/ft_malcom.h"

static uint8_t check_inval(char *input, t_malcom *mstruct)
{
	int32_t uncast = 0;

	if (!ft_isstrnumber(input)) {
		dprintf(STDERR, "ft_malcom: interval must be a valid number.\n");
		free_malcom_struct(mstruct);
		exit(EXIT_FAILURE);
	}

	uncast = ft_atoi(input);
	
	if (uncast < 0 || uncast > 255) {
		dprintf(STDERR, "ft_malcom: interval must be between 0 & 255.\n");
		free_malcom_struct(mstruct);
		exit(EXIT_FAILURE);
	}
	return ((uint8_t)uncast);
}

void	get_args(int start, int end, char **argv, t_malcom *mstruct)
{
	uint8_t get_arg_val = FALSE;

	for (uint8_t i = start; i < end; i++) {
		if (mstruct->mode & MALC_MODE_FLOOD)
		{
			if (get_arg_val) {
				check_inval(argv[i], mstruct);
				mstruct->options.optn_data[MALC_OPT_FLOOD_INVAL] = argv[i];
				get_arg_val = 0;
			}
			else if (argv[i][0] == '-') {
				if (!ft_strcmp("-i", argv[i])) {
					mstruct->options.flags |= MALC_OPT_FLOOD_INVAL;
					get_arg_val = MALC_OPT_FLOOD_INVAL;
				}
				else {
					free_malcom_struct(mstruct);
					invalid_option(argv[i]);
				}
			}
			else
			{
				if (!mstruct->dst_host.hostname)
					mstruct->dst_host.hostname = argv[i];
				else if (!mstruct->src_host.hostname)
					mstruct->src_host.hostname = argv[i];
				else {
					free_malcom_struct(mstruct);
					invalid_option(argv[i]);
				}
			}
		}
		else
		{
			if (!ft_strcmp("-R", argv[i])) {
				mstruct->options.flags |= MALC_OPT_POISON_REQBCK;
			} else {
				if (!mstruct->dst_host.hostname)
					mstruct->dst_host.hostname = argv[i];
				else if (!mstruct->dst_host.macstr)
					mstruct->dst_host.macstr = argv[i];
				else if (!mstruct->src_host.hostname)
					mstruct->src_host.hostname = argv[i];
				else if (!mstruct->src_host.macstr)
					mstruct->src_host.macstr = argv[i];
				else {
					free_malcom_struct(mstruct);
					invalid_option(argv[i]);
				}
			}
		}
	}

	if (get_arg_val) {
		if (get_arg_val & MALC_OPT_FLOOD_INVAL)
			dprintf(STDERR, "ft_malcom: Expected value for interval option.\n");
		free_malcom_struct(mstruct);
		exit(EXIT_FAILURE);
	}
}

void	get_options(int start, int end, char **argv, t_malcom *mstruct)
{
	for (uint8_t i = start; start < end; i++) {
		switch (mstruct->mode)
		{
		case MALC_MODE_POISON:
			if (end - i < 4 || end - i > 5)
			{
				dprintf(STDERR, "Too few / too many arguments to perform ARP poisoning.\n");
				free_malcom_struct(mstruct);
				display_usage(TRUE);
			}
			else {
				get_args(i, end, argv, mstruct);
				if (!mstruct->src_host.hostname || !mstruct->dst_host.hostname || !mstruct->src_host.macstr || !mstruct->dst_host.macstr) {
					dprintf(STDERR, "Too few / too many arguments to perform ARP poisoning.\n");
					free_malcom_struct(mstruct);
					display_usage(TRUE);
				}
				return ;
			}
			break;

		case MALC_MODE_FLOOD:
			if (end - i < 2 || end - i > 4)
			{
				dprintf(STDERR, "Too few / too many arguments to perform ARP flooding\n");
				free_malcom_struct(mstruct);
				display_usage(TRUE);
			}
			else {
				get_args(i, end, argv, mstruct);
				if (!mstruct->src_host.hostname || !mstruct->dst_host.hostname) {
					dprintf(STDERR, "Too few / too many arguments to perform ARP flooding\n");
					free_malcom_struct(mstruct);
					display_usage(TRUE);
				}
				return ;
			}
			break;
		case MALC_MODE_INTERACTIVE:
			return ;
		
		default:
			if (!ft_strcmp(argv[i], "-h"))
			{
				free_malcom_struct(mstruct);
				display_usage(TRUE);
			}

			if (!ft_strcmp(argv[i], "-v"))
			{
				mstruct->options.flags |= MALC_OPT_VERBOSE;
			}
			else if (!ft_strcmp(argv[i], "-I") && !mstruct->mode)
				mstruct->mode |= MALC_MODE_INTERACTIVE;
			else if (!ft_strcmp(argv[i], "-p") && !mstruct->mode)
				mstruct->mode |= MALC_MODE_POISON;
			else if (!ft_strcmp(argv[i], "-f") && !mstruct->mode)
				mstruct->mode |= MALC_MODE_FLOOD;
			else
			{
				free_malcom_struct(mstruct);
				invalid_option(argv[i]);
			}
			break;
		}
	}
}

void	parse(int argc, char **argv, t_malcom *mstruct)
{
	if (argc <= 1)
	{
		free_malcom_struct(mstruct);
		display_usage(TRUE);
	}
	get_options(1, argc, argv, mstruct);

	if (mstruct->mode & MALC_MODE_INTERACTIVE)
		return ;

	dnslookup(mstruct->dst_host.hostname, (t_sockaddr *)&(mstruct->dst_host.sock_addr_in), AF_INET);
	dnslookup(mstruct->src_host.hostname, (t_sockaddr *)&(mstruct->src_host.sock_addr_in), AF_INET);

	mstruct->src_host.ifa_name = is_ip_reachable(mstruct->src_host.sock_addr_in.sin_addr);
	mstruct->dst_host.ifa_name = is_ip_reachable(mstruct->dst_host.sock_addr_in.sin_addr);

	if (!mstruct->dst_host.ifa_name)
	{
		ip_is_not_reachable(mstruct->dst_host.sock_addr_in.sin_addr, mstruct->dst_host.hostname);
		free_malcom_struct(mstruct);
		exit(EXIT_FAILURE);
	}
	if (mstruct->src_host.ifa_name == NULL)
	{
		ip_is_not_reachable(mstruct->src_host.sock_addr_in.sin_addr, mstruct->src_host.hostname);
		free_malcom_struct(mstruct);
		exit(EXIT_FAILURE);
	}

	if (ft_strcmp(mstruct->dst_host.ifa_name, mstruct->src_host.ifa_name))
	{
		not_in_the_same_net(mstruct->src_host.hostname, mstruct->dst_host.hostname);
		exit(EXIT_FAILURE);
	}

	if (mstruct->mode == MALC_MODE_POISON) {
		if (stopkt(mstruct->dst_host.macstr, &(mstruct->dst_host.sock_addr_ll), ETH_P_ARP) < 0) {
			invalid_mac_addr(mstruct->dst_host.macstr);
			free_malcom_struct(mstruct);
			exit(EXIT_FAILURE);
		}
		if (stopkt(mstruct->src_host.macstr, &(mstruct->src_host.sock_addr_ll), ETH_P_ARP) < 0) {
			invalid_mac_addr(mstruct->src_host.macstr);
			free_malcom_struct(mstruct);
			exit(EXIT_FAILURE);
		}
	}

	printf("Found available interface: %s\n", mstruct->dst_host.ifa_name);
}