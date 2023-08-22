#include "philo.h"


void	free_philosophers(t_philo **philos, unsigned int count)
{
	unsigned int i;

	if (!philos)
		return;

	i = 0;
	while (i < count)
	{
		if (philos[i] != NULL)
		{
			pthread_mutex_destroy(&philos[i]->meal_time_lock);
			free(philos[i]);
		}
		i++;
	}

	free(philos);
}



static void assign_forks(t_philo *philo)
{
    int philo_count = philo->table->nb_philos;
    int first_fork = philo->id;
    int second_fork = (philo->id + 1) % philo_count;

    if (philo->id % 2)
    {
        first_fork = (philo->id + 1) % philo_count;
        second_fork = philo->id;
    }

    philo->fork[0] = first_fork;
    philo->fork[1] = second_fork;
}


size_t	ft_strlen(const char *s)
{
	const char	*eos;

	eos = s;
	while (*eos != '\0')
		eos++;
	return (eos - s);
}


t_philo **init_philosophers(t_table *table) ///static?????
{
	t_philo			**philos;
	unsigned int	i;
	char			*error_message;

	philos = malloc(sizeof(t_philo *) * table->nb_philos);
	if (!philos)
	{
		write(2, "Error: Failed to allocate memory for philosophers\n", 48);
		return (NULL);
	}

	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			error_message = "Error: Failed to allocate memory for a philosopher\n";
			write(2, error_message, ft_strlen(error_message));
			free_philosophers(philos, i); // Clean up previously allocated philosophers
			return (NULL);
		}

		if (pthread_mutex_init(&philos[i]->meal_time_lock, NULL) != 0)
		{
			error_message = "Error: Failed to initialize meal time mutex for philosopher\n";
			write(2, error_message, ft_strlen(error_message));
			free_philosophers(philos, i + 1); // Clean up previously allocated philosophers
			return (NULL);
		}

		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}

	return (philos);
}


static pthread_mutex_t *init_forks(t_table *table)
{
    pthread_mutex_t *forks;
    unsigned int i;

    forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
    if (!forks)
    {
        write(2, "Failed to allocate memory for forks\n", 36);
        return (NULL);
    }
    i = 0;
    while (i < table->nb_philos)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            write(2, "Failed to initialize fork mutex\n", 32);
            return (NULL);
        }
        i++;
    }
    return (forks);
}

bool init_global_mutexes(t_table *table) //static??
{
    table->fork_locks = init_forks(table);
    if (!table->fork_locks)
    {
        write(2, "Failed to initialize fork mutexes\n", 34);
        return (false);
    }
    if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0)
    {
        write(2, "Failed to initialize sim_stop_lock mutex\n", 40);
        return (false);
    }
    if (pthread_mutex_init(&table->write_lock, NULL) != 0)
    {
        write(2, "Failed to initialize write_lock mutex\n", 37);
        return (false);
    }
    return (true);
}


t_table *init_table(int ac, char **av, int i)
{
    t_table *table = malloc(sizeof(t_table));
    if (!table) {
        //error_null(STR_ERR_MALLOC, NULL, 0);
        return NULL;
    }

    table->nb_philos = parse_positive_integer(av[i++]);
    table->time_to_die = parse_positive_integer(av[i++]);
    table->time_to_eat = parse_positive_integer(av[i++]);
    table->time_to_sleep = parse_positive_integer(av[i++]);
    table->must_eat_count = (ac - 1 == 5) ? parse_positive_integer(av[i]) : -1;

    table->philos = init_philosophers(table);
    if (!table->philos) {
        free(table); // Clean up memory
        return NULL;
    }

    if (!init_global_mutexes(table)) {
        free(table->philos); // Clean up memory
        free(table);
        return NULL;
    }

    table->sim_stop = false;

    return table;
}


