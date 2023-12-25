/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:46:40 by badph             #+#    #+#             */
/*   Updated: 2023/12/26 00:05:14 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fk_lock_1(int sx, int dx)
{
	if (sx < dx)
		return (sx);
	return (dx);
}

int	fk_lock_2(int dx, int sx)
{
	if (dx < sx)
		return (sx);
	return (dx);
}

