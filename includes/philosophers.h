/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badph <badph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:46:44 by gbarone           #+#    #+#             */
/*   Updated: 2024/01/03 22:32:07 by badph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>

# define MAX_PHILOS 200
# define SUCCESS 0
# define DEATH_OCCURRED -1

typedef struct s_data
{
	pthread_t		observer;
	pthread_mutex_t	timestamp_mutex;
	pthread_mutex_t	meal_access_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	dad;
	pthread_mutex_t	*forks;
	int				is_it_running;
	int				n_p;
	int				number_of_meals;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				n_end;
	int				dead;
	int				all_satisfied;
	long long		time_start;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				fk1;
	int				fk0;
	t_data			*data;
	long long		tm_lst_meal;
	int				id_ph;
	int				burpo;
}	t_philo;

int			death_status(t_data *data);
void		*monitoraggio(void *ph);
int			ft_is_dead(t_philo *philo);
void		*life_cycle(void *ph);
void		ft_think(t_philo *philo);
void		ft_print_pd(t_philo *philo, char *str);
void		ft_mutexxx_init(t_data *data);
void		solitario(t_philo *philo);
void		ft_data_init(int ac, char **av, t_data *data);
int			starved(t_philo *philo, long long dt, long long tn);
void		ft_general_init(int ac, char **av, t_data *data, t_philo *philo);
void		ft_init_philo(t_philo *philo, t_data *data);
void		ft_data_init(int ac, char **av, t_data *data);
int			check(int ac, char **av);
void		ft_error(void);
void		ft_errorrrr(void);
int			ft_check_args(int ac, char **av);
bool		is_valid_input(int ac, char **av);
int			parse_positive_integer(char *str);
int			ft_atoi(const char *str);
void		philo_simulation(t_philo *philo);
int			death_status(t_data *data);
long long	ft_get_time_now(void);
long long	delta_time(long long time);
int			ft_sleep(t_philo *philo);
int			ft_eat(t_philo *philo);
void		*life_cycle(void *ph);
int			is_simulation_over(t_data *data);
void		init_last_meal_time(t_philo *philo);
void		ft_mutexxx_destroy(t_philo *philo);
int			min(int a, int b);
int			max(int a, int b);
void		init_last_meal_time(t_philo *philo);

#endif
