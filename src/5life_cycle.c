/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5life_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:59 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 15:32:53 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_simulation_over(t_data *data)
{
	return (data->all_satisfied || death_status(data));
}

void	assign_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->id_ph == philo->data->n_p)
	{
		*first_fork = max(philo->fk1, philo->fk2);
		*second_fork = min(philo->fk1, philo->fk2);
	}
	else
	{
		*first_fork = min(philo->fk1, philo->fk2);
		*second_fork = max(philo->fk1, philo->fk2);
	}
}

int	try_to_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	if (death_status(philo->data) == 1 || philo->data->all_satisfied == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (death_status(philo->data) == 1 || philo->data->all_satisfied == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		return (1);
	}
	ft_eat(philo);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	return (0);
}

void	*life_cycle(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->tm_lst_meal = ft_get_time_now();
	if (philo->id_ph == philo->data->n_p)
		usleep(250);
	while (!is_simulation_over(philo->data))
	{
		if (try_to_eat(philo) != SUCCESS)
			break ;
		if (is_simulation_over(philo->data))
			break ;
		if (ft_sleep(philo) != SUCCESS)
			break ;
		if (is_simulation_over(philo->data))
			break ;
		ft_think(philo);
	}
	return (NULL);
}
