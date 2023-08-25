#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"

typedef struct s_table t_table;
typedef struct s_philo t_philo;

int parse_positive_integer(char *str);
bool is_valid_input(int ac, char **av);
//static  bool    start_simulation(t_table *table);
void *philosopher(void *data);
time_t	get_time_in_ms(void);
int     gettimeofday(struct timeval * __restrict, void * __restrict);

t_philo **init_philosophers(t_table *table); //static???????
bool	init_global_mutexes(t_table *table);
size_t	ft_strlen(const char *s);

t_table *init_table(int ac, char **av);

void	free_philosophers(t_philo **philos, unsigned int count);

void ft_error(void);
void ft_errorr(void);
void ft_errorrrr(void);
bool	has_simulation_stopped(t_table *table);

typedef struct s_table {
    time_t          start_time; //
    unsigned int    nb_philos; //
    pthread_t       grim_reaper;
    time_t          time_to_die;//
    time_t          time_to_eat;//
    time_t          time_to_sleep;//
    int             must_eat_count;// //n_eat
    bool            sim_stop; //
    pthread_mutex_t sim_stop_lock; //
    pthread_mutex_t write_lock; //
    pthread_mutex_t *fork_locks; //
    t_philo         **philos; //
} t_table;

typedef struct s_philo {
    pthread_t       thread;
    unsigned int    id; //id
    unsigned int    times_ate;//n_eaten
    unsigned int    fork[2];
    pthread_mutex_t meal_time_lock;
    time_t          last_meal;
    t_table         *table; //table
} t_philo;

typedef enum {
    GOT_FORK_1,
    GOT_FORK_2,
    EATING,
    SLEEPING,
    THINKING,
    DIED
} t_status;


#endif /* PHILO_H */