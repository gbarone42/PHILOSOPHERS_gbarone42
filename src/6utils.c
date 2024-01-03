/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:05 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 22:27:08 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;

	i = 0;
	neg = 0;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	if (neg % 2 != 0)
		i = i * -1;
	return (i);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	init_last_meal_time(t_philo *philo)
{
	if (philo->tm_lst_meal == 0)
		philo->tm_lst_meal = ft_get_time_now();
}
