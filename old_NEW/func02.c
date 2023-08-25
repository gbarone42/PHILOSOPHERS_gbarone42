#include "philo.h"


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

size_t	ft_strlen(const char *s)
{
	const char	*eos;

	eos = s;
	while (*eos != '\0')
		eos++;
	return (eos - s);
}