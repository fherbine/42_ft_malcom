#include "../includes/ft_malcom.h"

t_time  timeval_to_ts(struct timeval dt)
{
        t_time ts;
        ts = ((double)dt.tv_sec * 1000) + ((double)dt.tv_usec / 1000);
        return (ts);
}

static t_time getnow(void)
{
        struct timeval now;
        gettimeofday(&now, NULL);
        return (timeval_to_ts(now));
}

void    ft_sleep(double sec)
{
        t_time start;
        start = getnow();
        while (getnow() - start < (sec * 1000)){};
}