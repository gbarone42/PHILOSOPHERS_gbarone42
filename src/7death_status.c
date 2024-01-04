/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7death_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:07 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/04 01:53:50 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	death_status(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->death);
	is_dead = (data->dead == 1);
	pthread_mutex_unlock(&data->death);
	return (is_dead);
}

int	starved(t_philo *philo, long long dt, long long tn)
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
			pthread_mutex_lock(&philo->data->death);
			printf("%llu the %d philosopher starved 💀 \n",
				delta_time(philo->data->time_start), philo[i].id_ph);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->death);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		i++;
	}
	return (0);
}

int	ft_is_dead(t_philo *philo)
{
	long long	dead_time;
	long long	current_time;
	int			ret;

	dead_time = (long long)philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->timestamp_mutex);
	current_time = ft_get_time_now();
	pthread_mutex_unlock(&philo->data->timestamp_mutex);
	ret = starved(philo, dead_time, current_time);
	return (ret);
}
