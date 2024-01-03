/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3thread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:55 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 13:03:05 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_start_thread(t_philo *philo)
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
	pthread_create(&philo->data->big_bro, NULL, ft_osserva, (void *)philo);
	while (i < philo->data->n_p)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->big_bro, NULL);
	return (NULL);
}

void	philo_simulation(t_philo *philo)
{
	ft_start_thread(philo);
	usleep(100);
	ft_destroyall(philo);
}
