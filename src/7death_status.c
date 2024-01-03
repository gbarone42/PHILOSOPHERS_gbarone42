/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7death_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:07 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 22:25:31 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	death_status(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dad);
	is_dead = (data->dead == 1);
	pthread_mutex_unlock(&data->dad);
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
