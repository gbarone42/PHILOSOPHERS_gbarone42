#include "philo.h"


time_t get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("\ntv_sec: %ld, tv_usec: %ld\n\n", tv.tv_sec, (long)tv.tv_usec);

    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


int	parse_positive_integer(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || nb > INT_MAX || nb == 0)
		return (-1);
	return ((int)nb);
}


bool	is_valid_input(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (0);

	i = 1;
	while (i < ac)
	{
		int nb = parse_positive_integer(av[i]);
		if (nb == -1)
			return (0);

		if (i == 1 && (nb < 1 || nb > MAX_PHILOS))
			return (0);

		i++;
	}

	return (1);
}



int validate_table(int ac, char **av)
{
    if (ac - 1 < 4 || ac - 1 > 5) 
	{
		ft_error();
        return 1;
    }
    if (!is_valid_input(ac, av))
	{
		ft_errorrrr();
        return 1;
    }
    return 0;
}