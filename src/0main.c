/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:05:48 by badph             #+#    #+#             */
/*   Updated: 2024/01/03 11:54:10 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!check(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
	if (philo == NULL)
	{
		free(data);
		return (1);
	}
	ft_general_init(ac, av, data, philo);
	if (data->n_p > 1)
		philo_simulation(philo);
	else
		ft_lonely_boy(philo);
	return (0);
}
