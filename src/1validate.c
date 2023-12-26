#include "../includes/philosophers.h"

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
	int	nb;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		nb = parse_positive_integer(av[i]);
		if (nb == -1)
			return (0);
		if (i == 1 && (nb < 1 || nb > MAX_PHILOS))
			return (0);
		i++;
	}
	return (1);
}

int	check(int ac, char **av)
{
	if (!is_valid_input(ac, av))
		ft_errorrrr();
	return (1);
}

// void parity(t_philo *philo)
// {
//     // Declare the variable
//     bool is_total_even;

//     // Assign the value to the variable
//     is_total_even = (philo->data->number_of_philos % 2 == 0);

//     // Apply the delay based on the parity of the total number and philosopher's ID
//     if ((is_total_even && philo->id_philo % 2 == 0) ||
//         (!is_total_even && philo->id_philo % 2 != 0)) {
//         usleep(100);
//     }
// }
