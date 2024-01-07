/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4time.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:57 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/04 17:15:10 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_get_time_now(void)
{
	struct timeval	tp;
	long long		ms;

	gettimeofday(&tp, NULL);
	ms = (tp.tv_sec * 1000) + (tp.tv_usec * 0.001);
	return (ms);
}

long long	diff_time(long long time)
{
	if (time > 0)
		return (ft_get_time_now() - time);
	return (0);
}
