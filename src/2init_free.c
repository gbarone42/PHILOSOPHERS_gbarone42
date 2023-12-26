#include "../includes/philosophers.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

void	ft_destroyall(t_philo *philo)
{
	int	i;

	i = 0;
	printf(COLOR_RED "\n..cleanup resources ✅ done..\n\n" COLOR_RESET);
	while (i < philo->data->number_of_philos)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->timestamp_mutex);
	pthread_mutex_destroy(&philo->data->meal_access_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->dad);
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

void	ft_data_init(int ac, char **av, t_data *data)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = 0;
	data->gburp = 1;// could be renamed 'is_simulation_running'
	data->all_satisfied = 0;
	return ;
}

void	ft_init_philo(t_philo *philo, t_data *data)//philo is an array of t_philo structures, each representing a philoso
{
	int	i;

	i = 0;
	if (!philo || !data)
		return;// Adding a safety check for null pointers.
	ft_mutexalo(data);// Initialize various mutexes in the t_data structure.
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_of_philos);//This line allocates memory for an array of mutexes (data->forks), with one mutex (fork) per philosopher. This ensures the total number of forks is equal to the number of philosophers.
	if (!data->forks)
		return ;
	while (i < data->number_of_philos)
	{
		philo[i].data = data;// Link each philosopher to the shared data structure.
		philo[i].fk1 = i;
		philo[i].fk2 = (i + 1) % data->number_of_philos;// Simplifying fork assignment.
		pthread_mutex_init(&data->forks[i], NULL);//initialize a mutex for each fork
		philo[i].id_philo = i + 1;
		philo[i].burpo = 0;// Rename 'burpo' to 'meal_count' for clarity.
		philo[i].time_last_meal = 0;
		i++;
	}
}

void	ft_general_init(int ac, char **av, t_data *data, t_philo *philo)
{
	ft_data_init(ac, av, data);// Initialize the data structure.
	ft_init_philo(philo, data);// Initialize the philosopher array.
}
