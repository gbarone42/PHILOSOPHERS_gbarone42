/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:17 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 15:30:58 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_is_dead(t_philo *philo)
{
	long long	dead_time;
	long long	current_time;
	int			ret;

	dead_time = (long long)philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->timestamp_mutex);
	current_time = ft_get_time_now();
	pthread_mutex_unlock(&philo->data->timestamp_mutex);
	ret = ft_ca(philo, dead_time, current_time);
	return (ret);
}

void	announce_satisfaction(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%llu 🌈 SATISFACTION\n", delta_time(philo->data->time_start));
	philo->data->all_satisfied = 1;
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_sazio(t_philo *philo)
{
	int	satisfied_count;
	int	i;

	satisfied_count = 0;
	i = 0;
	if (philo->data->number_of_meals <= 0)
	{
		return (0);
	}
	while (i < philo->data->n_p)
	{
		if (philo[i].burpo >= philo->data->number_of_meals)
		{
			satisfied_count++;
		}
		i++;
	}
	if (satisfied_count == philo->data->n_p)
	{
		announce_satisfaction(philo);
		return (1);
	}
	return (0);
}

void	*ft_osserva(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->data->number_of_meals > 0)
	{
		while (!philo->data->all_satisfied && !death_status(philo->data))
		{
			if (ft_is_dead(philo) || ft_sazio(philo))
				break ;
		}
	}
	else
	{
		while (!death_status(philo->data))
		{
			if (ft_is_dead(philo))
				break ;
		}
	}
	return (NULL);
}
