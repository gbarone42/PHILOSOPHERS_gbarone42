/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_orfane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:19 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 15:19:41 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_mutexalo(t_data *data)
{
	pthread_mutex_init(&data->timestamp_mutex, NULL);
	pthread_mutex_init(&data->meal_access_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dad, NULL);
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_lock(&data->dad);
	data->dead = 0 ;
	pthread_mutex_unlock(&data->dad);
}

void	ft_lonely_boy(t_philo *philo)
{
	printf("0 1 is thinking.. damn!!!\n");
	printf("0 1 has only a fork!\n");
	printf("0 1 has no chance to make it alive!\n");
	printf("%d 1 starved to death!\n", philo->data->time_to_die);
	ft_destroyall(philo);
}