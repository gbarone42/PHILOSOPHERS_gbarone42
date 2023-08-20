#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>

typedef struct s_config
{
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
} t_config;

typedef struct s_philosopher
{
    int id;
    t_config *config;
    pthread_mutex_t fork_mutexes[2]; // Left and right forks
} t_philosopher;

void parse_arguments(int argc, char *argv[], t_config *config);
void init_philosophers(t_philosopher *philosophers, t_config *config);
void *philosopher_thread(void *arg);
void *grim_reaper_thread(void *arg);
void print_timestamp(int id);
void log_action(int id, char *action);
void cleanup_resources(t_philosopher *philosophers, t_config *config);

#endif