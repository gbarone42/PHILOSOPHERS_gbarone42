/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2init_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:51 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 22:29:44 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_mutexxx_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_p)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->timestamp_mutex);
	pthread_mutex_destroy(&philo->data->meal_access_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->dad);
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

void	ft_mutexxx_init(t_data *data)
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

void	ft_data_init(int ac, char **av, t_data *data)
{
	data->n_p = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = 0;
	data->is_it_running = 1;
	data->all_satisfied = 0;
	return ;
}

void	ft_init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (!philo || !data)
		return ;
	ft_mutexxx_init(data);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_p);
	if (!data->forks)
		return ;
	while (i < data->n_p)
	{
		philo[i].data = data;
		philo[i].fk0 = i;
		philo[i].fk1 = (i + 1) % data->n_p;
		pthread_mutex_init(&data->forks[i], NULL);
		philo[i].id_ph = i + 1;
		philo[i].burpo = 0;
		philo[i].tm_lst_meal = ft_get_time_now();
		i++;
	}
}

void	ft_general_init(int ac, char **av, t_data *data, t_philo *philo)
{
	ft_data_init(ac, av, data);
	ft_init_philo(philo, data);
}
