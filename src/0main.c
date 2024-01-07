/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarone <gbarone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:05:48 by badph             #+#    #+#             */
/*   Updated: 2024/01/04 17:02:40 by gbarone          ###   ########.fr       */
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

void	solitario(t_philo *philo)
{
	printf("0 1 is thinking.. damn!!!\n");
	printf("0 1 has only a fork!\n");
	printf("0 1 has no chance to make it alive!\n");
	printf("%d 1 starved to death!\n", philo->data->time_to_die);
	write(1, "\n", 1);
	write(1, "        .-\"\"\"\"\"\"-.\n", 20);
	write(1, "      .'          '.\n", 22);
	write(1, "     /   O      O   \\\n", 23);
	write(1, "    :           `    :\n", 23);
	write(1, "    |           `    |   \n", 27);
	write(1, "    :    .------.    :\n", 24);
	write(1, "     \\  '        '  /\n", 23);
	write(1, "      '.          .'\n", 22);
	write(1, "        '-......-'\n", 20);
	write(1, "\n", 1);
	ft_mutexxx_destroy(philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!check(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
	if (philo == NULL)
	{
		free(data);
		return (1);
	}
	ft_general_init(ac, av, data, philo);
	if (data->n_p > 1)
		philo_simulation(philo);
	else
		solitario(philo);
	return (0);
}
