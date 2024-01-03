/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6err.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:01:02 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 13:03:05 by gbarone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_errorrrr(void)
{
	write(1, "\n", 1);
	write(1, "   <°)))><       \n", 20);
	write(1, "\n\033[1;31mError\033[0m\n\n", 19);
	write(1, "     /\\_/\\     \n", 17);
	write(1, "    ( o.o )    \n", 16);
	write(1, "    > ^ <    42\n", 17);
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError03\033[0m\n\n", 22);
	write(1, "\n", 1);
	exit(1);
}

void	ft_error(void)
{
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError\033[0m\n\n", 19);
	write(1, "     /\\_/\\     \n", 16);
	write(1, "    ( o.o )    \n", 16);
	write(1, "    > ^ <    42\n", 16);
	write(1, "\n", 1);
	write(1, "\n\033[1;31mError01\033[0m\n\n", 21);
	write(1, "\n", 1);
	exit(1);
}
