#include "../includes/ft_malcom.h"

void display_mstruct(t_malcom *mstruct)
{
	printf("Malcom struct:\n");
	printf(" mode: %s\n", ft_itoa_base(mstruct->mode, 16));
	printf(" Src host:\n");
	printf("  hostname: %s\n", mstruct->src_host.hostname);
	printf("  MAC: %s\n", mstruct->src_host.macstr);
	printf(" Dst host:\n");
	printf("  hostname: %s\n", mstruct->dst_host.hostname);
	printf("  MAC: %s\n", mstruct->dst_host.macstr);
	printf(" options:\n");
	printf("  flags: %s\n", ft_itoa_base(mstruct->options.flags, 16));
}