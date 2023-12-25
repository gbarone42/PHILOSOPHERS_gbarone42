#include "../includes/philosophers.h"

long long	ft_get_time_now(void)
{
	struct timeval	tp;
	long long		ms;

	gettimeofday(&tp, NULL);
	ms = (tp.tv_sec * 1000) + (tp.tv_usec * 0.001);
	return (ms);
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (ft_get_time_now() - time);
	return (0);
}