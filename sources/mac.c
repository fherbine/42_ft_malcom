#include "../includes/ft_malcom.h"

int		stopkt(char *macstr, t_sockaddr_ll *sa_pkt, uint16_t eth_proto)
{
	char range[16] = "0123456789abcdef";
	char **splitted = NULL;
	uint8_t i = 0;

	if (!macstr || ft_strlen(macstr) != 17)
		return (-1);
	
	splitted = ft_strsplit(macstr, ':');

	while (splitted[i])
	{
		if (ft_strlen(splitted[i]) != 2)
			return (-1);
		
		if (!ft_strchr(range, splitted[i][0]) || !ft_strchr(range, splitted[i][1]))
			return (-1);

		sa_pkt->sll_addr[i] = (unsigned char) ft_atoi_base(splitted[i], 16);
		i++;
	}
	ft_free_tab(splitted);

	sa_pkt->sll_family = AF_PACKET;
	sa_pkt->sll_halen = ETH_ALEN;
	sa_pkt->sll_hatype = ARPHRD_ETHER;
	sa_pkt->sll_protocol = htons(eth_proto);
	sa_pkt->sll_ifindex = is_mac_in_ifs(sa_pkt->sll_addr);
	return (0);
}

char	*pkttos(void *ha_addr)
{
	char *byte, *_byte;
	char *macstr = ft_strdup("");
	for (uint8_t i = 0; i < ETH_ALEN; i++)
	{
		byte = ft_itoa_base(((unsigned char *)ha_addr)[i], 16);
		if (ft_strlen(byte) == 1) {
			_byte = ft_strjoin(ft_strdup("0"), byte);
			free(byte);
			byte = _byte;
		}
		macstr = ft_strjoin(macstr, byte);
		if (i < 5)
			macstr = ft_strjoin(macstr, ":");
		free(byte);
	}
	return (macstr);
}

int		maccmp(uint8_t *addr1, uint8_t *addr2)
{
	for (int i = 0; i < ETH_ALEN; i++){
		if (addr1[i] != addr2[i])
			return (addr1[i] - addr2[i]);
	}
	return (0);
}