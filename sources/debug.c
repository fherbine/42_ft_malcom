#include "../includes/ft_malcom.h"

void display_mstruct(t_malcom *mstruct)
{
	printf("Malcom struct:\n");
	printf(" mode: %s\n", ft_itoa_base(mstruct->mode, 16));
	printf(" Src host:\n");
	printf("  hostname: %s\n", mstruct->src_host.hostname);
	printf("  IP: %s\n", inet_ntoa(mstruct->src_host.sock_addr_in.sin_addr));
	printf("  MAC: %s\n", mstruct->src_host.macstr);
	printf(" Dst host:\n");
	printf("  hostname: %s\n", mstruct->dst_host.hostname);
	printf("  IP: %s\n", inet_ntoa(mstruct->dst_host.sock_addr_in.sin_addr));
	printf("  MAC: %s\n", mstruct->dst_host.macstr);
	printf(" options:\n");
	printf("  flags: %s\n", ft_itoa_base(mstruct->options.flags, 16));
}

void print_buffer(void *buffer_addr, ssize_t len)
{
	ssize_t count = 0;

	while (count < len)
	{
		if (count % 8 == 0)
			printf("%02ld | " , (len / 8) - (count / 8));

		printf("%02X ", *((uint8_t *)buffer_addr++));

		if ((count + 1) % 8 == 0 && count)
			printf("\n");

		count++;
	}
	printf("\n");
}