
#include "../includes/philosophers.h"

void	ft_mutexalo(t_data *data)
{
	pthread_mutex_init(&data->timestamp_mutex, NULL);//timestamp_mutex
	pthread_mutex_init(&data->meal_access_mutex, NULL);//meal_access_mutex
	pthread_mutex_init(&data->print_mutex, NULL);//print_mutex
	pthread_mutex_init(&data->dad, NULL);//control_mutex
	pthread_mutex_init(&data->last_meal_mutex, NULL);//last_meal_mutex
	pthread_mutex_lock(&data->dad);
	data->dead = 0 ;//indicating no philosopher is dead
	pthread_mutex_unlock(&data->dad);
}

void	ft_lonely_boy(t_philo *philo)
{
	printf("0 the loneliest philosopher is thinking\n");
	printf("0 he took just one chopstick\n");
	printf("0 he can't eat with just a single chopstick\n");
	printf("%d 1 starved to death 💀 \n", philo->data->time_to_die);
	ft_destroyall(philo);
}
