#include "philo.h"

void	ft_destroyall(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->nb_philos)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->table->timewarp);
	pthread_mutex_destroy(&philo->table->kmangia);
	pthread_mutex_destroy(&philo->table->stampa);
	pthread_mutex_destroy(&philo->table->dad);
	pthread_mutex_destroy(&philo->table->lastmeal);
	free(philo->table->forks);
	free(philo->table);
	free(philo);
}

int main(int ac, char **av)
{
    t_table *table;
	t_philo	*philo;

    if (validate_table(ac, av) == 0)
    {	
		// Error occurred during validation or initialization  
		table = malloc(sizeof(t_table));
		philo = malloc(sizeof(t_philo) * (parse_positive_integer(av[1]) + 1));
		init_table_params(ac, av, table);
		init_philosophers(philo, table);
       // printf("Address of table: %p\n", (void *)table);
       // printf("Address of philos: %p\n", (void *)table->philos);
		if (table->nb_philos > 1)
		{
			ft_start_thread(philo);
			usleep(10000);
			ft_destroyall(philo);
		}
		//else
		//ft_lonely_boy(philo);
    }
    return 0;
}

