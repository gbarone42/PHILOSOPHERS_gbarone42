/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3thread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:55 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 22:28:46 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*threads_start(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->time_start = ft_get_time_now();
	while (i < philo->data->n_p)
	{
		pthread_create(&philo[i].thread, NULL, life_cycle, (void *)&philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&philo->data->observer, NULL, monitoraggio, (void *)philo);
	while (i < philo->data->n_p)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->observer, NULL);
	return (NULL);
}

void	philo_simulation(t_philo *philo)
{
	threads_start(philo);
	usleep(100);
	ft_mutexxx_destroy(philo);
}
