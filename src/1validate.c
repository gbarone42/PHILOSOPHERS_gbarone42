/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1validate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:46 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 13:03:05 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	parity(t_philo *philo)
{
	bool	is_total_even;

	is_total_even = (philo->data->n_p % 2 == 0);
	if (is_total_even)
	{
		usleep(100);
	}
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
	int	nb;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
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
