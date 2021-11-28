#include "../includes/ft_malcom.h"

int		stopkt(char *macstr, t_sockaddr_pkt *sa_pkt)
{
	char **splitted = NULL;
	uint8_t i = 0;

	if (!macstr || ft_strlen(macstr) != 17)
		return (-1);
	
	splitted = ft_strsplit(macstr, ':');

	while (splitted[i])
	{
		sa_pkt->spkt_device[i] = (char)ft_atoi_base(splitted[i], 16);
		i++;
	}
	ft_free_tab(splitted);
	return (0);
}

char *pkttos(t_sockaddr_pkt *sa_pkt)
{
	char *byte;
	char *macstr = ft_strdup("");
	for (uint8_t i = 0; i < 6; i++)
	{
		byte = ft_itoa_base(sa_pkt->spkt_device[i], 16);
		ft_strjoin(macstr, byte);
		if (i < 5)
			ft_strjoin(macstr, ":");
	}
	return (macstr);
}