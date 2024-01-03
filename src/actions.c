/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:03:02 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 13:40:03 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_stampa_pd(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (death_status(philo->data) == 1 || philo->data->all_satisfied == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%llu %d %s\n",
		delta_time(philo->data->time_start), philo->id_ph, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_sleep(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return (DEATH_OCCURRED);
	ft_stampa_pd(philo, "is sleepin 🌙");
	usleep(philo->data->time_to_sleep * 1000);
	return (SUCCESS);
}

void	ft_think(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return ;
	ft_stampa_pd(philo, "is thinkin..");
}

int	ft_eat(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return (DEATH_OCCURRED);
	ft_stampa_pd(philo, "took a chopstick");
	ft_stampa_pd(philo, "took both chopsticks 🥢");
	if (death_status(philo->data) == 1)
		return (DEATH_OCCURRED);
	philo->burpo += 1;
	ft_stampa_pd(philo, "is eating🍗");
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	if (death_status(philo->data) == 0)
	{
		philo->tm_lst_meal = ft_get_time_now();
	}
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	return (SUCCESS);
}
