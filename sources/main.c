#include "../includes/ft_malcom.h"

static t_malcom	*get_malcom_struct(void)
{
	t_malcom *mstruct = NULL;
	if (!(mstruct = (t_malcom *)malloc(sizeof(t_malcom))))
		exit(EXIT_FAILURE);
	
	ft_bzero(mstruct, sizeof(*mstruct));
	return (mstruct);
}

void	free_malcom_struct(t_malcom *mstruct)
{
	if (mstruct->src_host.ifa_name)
		free(mstruct->src_host.ifa_name);
	if (mstruct->dst_host.ifa_name)
		free(mstruct->dst_host.ifa_name);
	free(mstruct);
}

void display_ifs(void)
{
	t_ifaddrs	*ifs = NULL, *ptr = NULL;
	char family[16];

	if ((getifaddrs(&ifs)) < 0)
		exit(EXIT_FAILURE);

	ptr = ifs;

	while (ptr)
	{
		ft_strclr(family);

		if (ptr->ifa_addr->sa_family == AF_INET)
			ft_strcpy(family, "AF_INET");
		else if (ptr->ifa_addr->sa_family == AF_INET6)
			ft_strcpy(family, "AF_INET6");
		else if (ptr->ifa_addr->sa_family == AF_PACKET)
			ft_strcpy(family, "AF_PACKET");
		else
			ft_strcpy(family, "undefined");

		printf("name: %s, flags: %x, family: %s",
			ptr->ifa_name, ptr->ifa_flags, family);

		if (ptr->ifa_addr->sa_family == AF_PACKET){
			printf("-%d-", ((t_sockaddr_ll *)ptr->ifa_addr)->sll_ifindex);
			printf("\tMAC: %s", pkttos(((t_sockaddr_ll *)ptr->ifa_addr)->sll_addr));
		}
		else if (ptr->ifa_addr->sa_family == AF_INET){
			printf("\tIPv4: %s", inet_ntoa(((t_sockaddr_in *)ptr->ifa_addr)->sin_addr));
			printf("\tIPv4 netmask: %s", inet_ntoa(((t_sockaddr_in *)ptr->ifa_netmask)->sin_addr));
			printf("\tIPv4 dstaddr: %s", inet_ntoa(((t_sockaddr_in *)ptr->ifa_dstaddr)->sin_addr));
			printf("\tIPv4 brdaddr: %s", inet_ntoa(((t_sockaddr_in *)ptr->ifa_broadaddr)->sin_addr));
		}
		printf("\n");
		ptr = ptr->ifa_next;
	}
	
	freeifaddrs(ifs);
}

int main(int argc, char **argv)
{
	t_malcom *mstruct = get_malcom_struct();
	parse(argc, argv, mstruct);
	create_arp_socket(mstruct);

	if (mstruct->mode & MALC_MODE_POISON)
		arp_poison(mstruct);
	else if (mstruct->mode & MALC_MODE_FLOOD)
		arp_flooding(mstruct);
	
	free_malcom_struct(mstruct);
}