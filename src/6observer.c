/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6observer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:17 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/04 19:01:45 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	announce_satisfaction(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->satisfied);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%llu 🌈 SATISFACTION\n", diff_time(philo->data->start_time));
	philo->data->all_satisfied = 1;
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->satisfied);
}

int	is_satisfaction(t_philo *philo)
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
		pthread_mutex_lock(&philo->data->burpo_mutex);
		if (philo[i].burpo >= philo->data->number_of_meals)
		{
			satisfied_count++;
		}
		pthread_mutex_unlock(&philo->data->burpo_mutex);
		i++;
	}
	if (satisfied_count == philo->data->n_p)
	{
		announce_satisfaction(philo);
		return (1);
	}
	return (0);
}

void	*monitoraggio(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->data->number_of_meals > 0)
	{
		while (!philo->data->all_satisfied && !death_status(philo->data))
		{
			if (ft_is_dead(philo) || is_satisfaction(philo))
				break ;
			usleep(100);
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
