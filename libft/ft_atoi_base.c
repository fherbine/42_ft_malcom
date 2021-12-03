#include "libft.h"

static int32_t	strgetidx(char *s, char c)
{
	for (int32_t i = 0; i < (int32_t)ft_strlen(s); i++) {
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

long long	ft_atoi_base(const char *str, uint8_t base)
{
	size_t	i;
	int		sgn;
	int		res;
	char	map[] = "0123456789abcdef";

	if (!str)
		return (0);

	if (base > 16)
		return (0);

	char	*bmap = ft_strsub(map, 0, base);
	i = 0;
	sgn = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r' \
			|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sgn = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (ft_strchr(bmap, str[i]) && str[i])
	{
		int32_t add = (int32_t)strgetidx(bmap, str[i]);
		
		if (add < 0)
			return (0);

		res = add + base * res;
		i++;
	}
	free(bmap);
	return (res * sgn);
}