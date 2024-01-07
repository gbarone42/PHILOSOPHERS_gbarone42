/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5life_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:59 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/04 19:52:53 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_simulation_over(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->satisfied);
	if (data->all_satisfied == 1)
		ret = 1;
	else
		ret = death_status(data);
	pthread_mutex_unlock(&data->satisfied);
	return (ret);
}

void	assign_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->id_ph == philo->data->n_p)
	{
		*first_fork = max(philo->fk1, philo->fk0);
		*second_fork = min(philo->fk1, philo->fk0);
	}
	else
	{
		*first_fork = min(philo->fk1, philo->fk0);
		*second_fork = max(philo->fk1, philo->fk0);
	}
}

int	try_to_eat(t_philo *philo, int all_satisfied)
{
	int	first_fork;
	int	second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	if (death_status(philo->data) == 1 || all_satisfied == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (death_status(philo->data) == 1 || all_satisfied == 1)
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
	int		satisfied;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->time_last_meal = ft_get_time_now();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	while (!is_simulation_over(philo->data))
	{
		pthread_mutex_lock(&philo->data->satisfied);
		satisfied = philo->data->all_satisfied;
		pthread_mutex_unlock(&philo->data->satisfied);
		if (try_to_eat(philo, satisfied) != SUCCESS)
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
