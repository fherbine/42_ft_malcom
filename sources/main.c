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

int main(int argc, char **argv)
{
	t_malcom *mstruct = get_malcom_struct();
	parse(argc, argv, mstruct);
	create_arp_socket(mstruct);

	if (mstruct->mode & MALC_MODE_POISON)
		arp_poison(mstruct);
	else if (mstruct->mode & MALC_MODE_FLOOD)
		arp_flooding(mstruct);
	else if (mstruct->mode & MALC_MODE_INTERACTIVE)
		interactive(mstruct);

	free_malcom_struct(mstruct);
}