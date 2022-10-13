#include "libft.h"
uint8_t ft_isstrnumber(char *str) {
    if (str[0] != '-' && !ft_isdigit(str[0]))
        return 0;

    for (int i = 0; str[i]; i++) {
        if (!ft_isdigit(str[i]))
            return 0;
    }

    return 1;
}