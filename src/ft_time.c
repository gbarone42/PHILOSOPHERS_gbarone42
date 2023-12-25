/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:46:29 by badph             #+#    #+#             */
/*   Updated: 2023/12/26 00:04:45 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


int	ft_ca(t_philo *philo, long long dt, long long tn)
{
	int			i;

	i = 0;
	while (i < philo->data->number_of_philos)
	{
		if (tn - philo[i].time_last_meal > dt)//checks if the time elapsed since the last meal of the current philosopher (philo[i].time_last_meal) exceeds the death threshold (dt)
		{
			pthread_mutex_lock(&philo->data->print_mutex);
			pthread_mutex_lock(&philo->data->dad);
			printf("%llu the %d philosopher starved 💀 \n",
				delta_time(philo->data->time_start), philo[i].id_philo);//delta_time function is used to calculate the time elapsed since the start of the simulation
			philo->data->dead = 1;//setting the dead flag 
			pthread_mutex_unlock(&philo->data->dad);
			pthread_mutex_unlock(&philo->data->print_mutex);
			//pthread_mutex_unlock(&philo->data->last_meal_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}



int	ft_print_error(void)
{
	printf("Invalid parameters!\n");
	return (0);
}
