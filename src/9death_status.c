/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9death_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:07 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 13:03:05 by gbarone          ###   ########.fr       */
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
