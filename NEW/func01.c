#include "philo.h"

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
	write(1,"9999",4);
    table->fork_locks = init_forks(table);
    if (!table->fork_locks)
    {
        write(2, "Failed to initialize fork mutexes\n", 34);
        return (0);
    }
    if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0)
    {
        write(2, "Failed to initialize sim_stop_lock mutex\n", 40);
        return (0);
    }
    if (pthread_mutex_init(&table->write_lock, NULL) != 0)
    {
        write(2, "Failed to initialize write_lock mutex\n", 37);
        return (0);
    }
    return (1);
}




t_table *init_table_params(int ac, char **av, int *index)
{
    t_table *table;
    
    table = malloc(sizeof(t_table));

    if (!table)
    {
        // Handle memory allocation error
        return NULL;
    }
    *index = 1; // Start index for parsing command-line arguments
    table->nb_philos = parse_positive_integer(av[(*index)++]);
    table->time_to_die = parse_positive_integer(av[(*index)++]);
    table->time_to_eat = parse_positive_integer(av[(*index)++]);
    table->time_to_sleep = parse_positive_integer(av[(*index)++]);
    table->must_eat_count = (ac - 1 == 5) ? parse_positive_integer(av[(*index)]) : -1;
    return table;
}

t_table *init_table(int ac, char **av)
{
    int index;
    t_table *table;

    table = init_table_params(ac, av, &index);
    if (!table)
    {
        // Handle initialization error
        return NULL;
    }

    printf("nb_philos: %d\n", table->nb_philos);
    printf("time_to_die: %ld\n", table->time_to_die);
    printf("time_to_eat: %ld\n", table->time_to_eat);
    printf("time_to_sleep: %ld\n", table->time_to_sleep);
    printf("must_eat_count: %d\n", table->must_eat_count);

    table->philos = init_philosophers(table);
    if (!table->philos)
    {
        // Handle philosophers initialization error
        free(table); // Clean up memory
        return NULL;
    }
    if (!init_global_mutexes(table))
    {
        // Handle global mutexes initialization error
        free(table->philos); // Clean up memory
        free(table);
        return NULL;
    }
    table->sim_stop = 0;
    return table;
}




/*static t_philo **allocate_philosophers(t_table *table)
{
    t_philo **philos;

    philos = malloc(sizeof(t_philo *) * table->nb_philos);
    if (!philos)
    {
        write(2, "Error: Failed to allocate memory for philosophers\n", 48);
        return (NULL);
    }
    return philos;
}

static bool initialize_philosopher(t_philo *philo, t_table *table, unsigned int id)
{
    char *error_message;

    philo = malloc(sizeof(t_philo));
    if (!philo)
    {
        error_message = "Error: Failed to allocate memory for a philosopher\n";
        write(2, error_message, ft_strlen(error_message));
        return (false);
    }

    if (pthread_mutex_init(&philo->meal_time_lock, NULL) != 0)
    {
        error_message = "Error: Failed to initialize meal time mutex for philosopher\n";
        write(2, error_message, ft_strlen(error_message));
        free(philo);
        return (false);
    }

    philo->table = table;
    philo->id = id;
    philo->times_ate = 0;
    assign_forks(philo);

    return (true);
}

t_philo **init_philosophers(t_table *table)
{
    t_philo **philos;
    unsigned int i;

    write(1, "7777", 4);
    philos = allocate_philosophers(table);
    if (!philos)
        return (NULL);

    i = 0;
    while (i < table->nb_philos)
    {
        if (!initialize_philosopher(philos[i], table, i))
        {
            free_philosophers(philos, i); // Clean up previously allocated philosophers
            return (NULL);
        }
        i++;
    }

    return (philos);
}*/