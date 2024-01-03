/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:37 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 15:20:03 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_ca(t_philo *philo, long long dt, long long tn)
{
	int			i;

	i = 0;
	while (i < philo->data->n_p)
	{
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		if (tn - philo[i].tm_lst_meal > dt)
		{
			pthread_mutex_unlock(&philo->data->last_meal_mutex);
			pthread_mutex_lock(&philo->data->print_mutex);
			pthread_mutex_lock(&philo->data->dad);
			printf("%llu the %d philosopher starved 💀 \n",
				delta_time(philo->data->time_start), philo[i].id_ph);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->dad);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		i++;
	}
	return (0);
}
