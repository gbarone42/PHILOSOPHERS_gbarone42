#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"



typedef struct s_table {
    time_t          start_time; 
    int    nb_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_of_meals;
    pthread_mutex_t	*forks;////
    int				dead;//
     long long		time_start; //
     int				gburp;//
     int				sazi;//
    pthread_mutex_t	timewarp;
    pthread_mutex_t	kmangia;
    pthread_mutex_t	stampa;
    pthread_mutex_t	lastmeal;
    pthread_mutex_t	dad;
    pthread_t		big_bro;
} t_table;


typedef struct s_philo {

    int				philo_id;//
	t_table	*table;///
    pthread_t		thread;//
    int				fk1;//
	int				fk2;//
    int				burpo;//
    long long		last_meal;//
} t_philo;




typedef enum {
    GOT_FORK_1,
    GOT_FORK_2,
    EATING,
    SLEEPING,
    THINKING,
    DIED
} t_status;


typedef struct s_table t_table;
typedef struct s_philo t_philo;

int parse_positive_integer(char *str);
bool is_valid_input(int ac, char **av);
time_t	get_time_in_ms(void);
int     gettimeofday(struct timeval * __restrict, void * __restrict);


void init_table_params(int ac, char **av, t_table *table);
void init_philosophers(t_philo *philo,t_table *tabl);
void	init_global_mutexes(t_table *table);
void	*ft_start_thread(t_philo *philo);
void	*ft_simposio(void *ph);
int	check_morte(t_table *data);
void	*ft_osserva(void *ph);


t_table *init_table(int ac, char **av);
int validate_table(int ac, char **av);
void ft_error(void);
void ft_errorr(void);
void ft_errorrrr(void);


#endif /* PHILO_H */