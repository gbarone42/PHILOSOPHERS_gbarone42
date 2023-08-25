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


static t_philo **allocate_philosophers(t_table *table)
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

    // Print the address of the philo pointer
    printf("Address of philo pointer: %p\n", (void *)&philo);

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
    {
        write(1, "www", 3);
        return NULL;
    }
    printf("Value of philos: %p\n", (void *)philos); // Print the value of philos
    write(1, "zzz", 3);
    i = 0;
    while (i < (unsigned int)table->nb_philos)
    {
        write(1, "QWQ", 3);
        if (!initialize_philosopher(philos[i], table, i))
        {
            write(1,"NNNN",4);
            printf("Error initializing philosopher %d\n", i);
            free_philosophers(philos, i); // Clean up previously allocated philosophers
            return NULL;
        }
        i++;
    }
    write(1, "TTT", 3);
    return (philos);
}
