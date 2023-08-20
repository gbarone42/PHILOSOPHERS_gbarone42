// philo_bonus.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

void parse_arguments(int argc, char *argv[], t_config *config)
{
    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "Usage: %s num_philosophers time_to_die time_to_eat time_to_sleep [num_times_to_eat]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    config->num_philosophers = atoi(argv[1]);
    config->time_to_die = atoi(argv[2]);
    config->time_to_eat = atoi(argv[3]);
    config->time_to_sleep = atoi(argv[4]);

    if (argc == 6)
        config->num_times_to_eat = atoi(argv[5]);
}

void init_philosophers(t_philosopher *philosophers, t_config *config)
{
    for (int i = 0; i < config->num_philosophers; i++)
    {
        philosophers[i].id = i + 1;
        philosophers[i].config = config;
        pthread_mutex_init(&philosophers[i].fork_mutexes[0], NULL);
        pthread_mutex_init(&philosophers[i].fork_mutexes[1], NULL);
    }
}

void *philosopher_thread(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;
    int id = philosopher->id;
    t_config *config = philosopher->config;

    while (1)
    {
        // Thinking
        printf("%d is thinking\n", id);
        usleep(config->time_to_sleep * 1000);

        // Pick up forks
        pthread_mutex_lock(&philosopher->fork_mutexes[0]);
        printf("%d has taken a fork\n", id);
        pthread_mutex_lock(&philosopher->fork_mutexes[1]);
        printf("%d has taken another fork\n", id);

        // Eating
        printf("%d is eating\n", id);
        usleep(config->time_to_eat * 1000);

        // Put down forks
        pthread_mutex_unlock(&philosopher->fork_mutexes[0]);
        pthread_mutex_unlock(&philosopher->fork_mutexes[1]);
    }

    return NULL;
}

void *grim_reaper_thread(void *arg)
{
    (void)arg; // Mark the parameter as unused

    // Implement termination conditions here

    return NULL;
}
void print_timestamp(int id)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    printf("%llu %d ", ms, id);
}

void log_action(int id, char *action)
{
    print_timestamp(id);
    printf("%s\n", action);
}

void cleanup_resources(t_philosopher *philosophers, t_config *config)
{
    for (int i = 0; i < config->num_philosophers; i++)
    {
        pthread_mutex_destroy(&philosophers[i].fork_mutexes[0]);
        pthread_mutex_destroy(&philosophers[i].fork_mutexes[1]);
    }
}

int main(int argc, char *argv[])
{
    t_config config;
    parse_arguments(argc, argv, &config);

    t_philosopher philosophers[config.num_philosophers];
    init_philosophers(philosophers, &config);

    pthread_t philosopher_threads[config.num_philosophers];
    for (int i = 0; i < config.num_philosophers; i++)
    {
        pthread_create(&philosopher_threads[i], NULL, philosopher_thread, &philosophers[i]);
    }

	pthread_t grim_reaper_thread_id;
	pthread_create(&grim_reaper_thread_id, NULL, grim_reaper_thread, NULL);

    // Wait for philosopher threads to finish (not shown here)
    // Wait for grim reaper thread to finish (not shown here)

    cleanup_resources(philosophers, &config);

    return 0;
}