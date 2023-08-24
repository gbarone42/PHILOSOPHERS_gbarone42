#include "philo.h"


int validate_and_initialize_table(int ac, char **av, t_table **table)
{
    if (ac - 1 < 4 || ac - 1 > 5) 
	{
		ft_error();
        return 1;
    }
    if (!is_valid_input(ac, av))
	{
		ft_errorr();
        return 1;
    }
    *table = init_table(ac, av);
    if (!(*table))
	{
		//write(1,"===9",4);
        ft_errorr();
        return 1;
    }
    return 0;
}




void print_status_with_time(t_philo *philo, t_status status)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long timestamp_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    const char *status_strings[] = {
        "got fork 1",
        "got fork 2",
        "is eating",
        "is sleeping",
        "is thinking",
        "died"
    };

    printf("[%lld] Philosopher %d %s\n", timestamp_ms, philo->id, status_strings[status]);
}



static void *lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
    print_status_with_time(philo, GOT_FORK_1);

    philo_sleep(philo->table, philo->table->time_to_die);

    print_status_with_time(philo, DIED);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);

    return NULL;
}

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void synchronize_start(time_t start_time)
{
    while (get_time_in_ms() < start_time)
    {
        // This loop continues as long as the current time is less than the start time.
        // It effectively waits for the start time to be reached before moving on.
    }
}

void *philosopher(void *data)
{
    t_philo *philo = (t_philo *)data;

    // Set the last meal time to the simulation start time
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_lock);

    // Delay the philosopher's start time
    synchronize_start(philo->table->start_time);

    // Check if time_to_die is set to 0, if yes, return immediately
    if (philo->table->time_to_die == 0)
        return (void *)0;

    // Handle a single philosopher scenario
    if (philo->table->nb_philos == 1)
        return (void *)(intptr_t)lone_philo_routine(philo);

    // For odd-id philosophers, start by thinking
    if (philo->id % 2)
        think_routine(philo, (void *)1);

    // Continue actions while simulation is ongoing
    while (!has_simulation_stopped(philo->table))
    {
        eat_sleep_routine(philo);
        think_routine(philo, (void *)0);
    }

    return (void *)0;
}



static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->grim_reaper, NULL,
				&grim_reaper, table) != 0)
			return (-1);
	}
	return (0);
}


int main(int ac, char **av)
{
    t_table *table;

    if (validate_and_initialize_table(ac, av, &table) != 0)
    {
        // Error occurred during validation or initialization
        return -1;
    }
    if (!table)
		return (-1);
	if (!start_simulation(table))
		return (-1);
    // Create philosopher threads here and start the simulation
	//write(1,"ekko",4);
    return 0;
}