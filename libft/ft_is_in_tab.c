#include "./libft.h"

uint8_t	ft_is_in_tab(char **tab, char *elem)
{
	int i = 0;
	if (!tab)
		return (0);
		
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], elem))
			return (1);
		i++;
	}
	return (0);
}