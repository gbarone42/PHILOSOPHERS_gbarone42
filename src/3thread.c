#include "../includes/philosophers.h"
 //ft_even_odd
 //purpose of this function is to reduce the likelihood of deadlock in a
 //situation where multiple threads (philosophers) are competing for shared
 //resources (such as forks)
 // 
 //the function aims to stagger their actions slightly,
 //reducing the chance that they will all try to access
 //resources at the same exact time.
 //such delays can help in preventing situations where all philosophers
 //pick up one fork and then wait indefinitely for the other (a classic deadlock scenario)

void	*ft_start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->time_start = ft_get_time_now();
	//one thread per philosopher
	while (i < philo->data->number_of_philos)
	{
		//parity(&philo[i]);
		pthread_create(&philo[i].thread, NULL, life_cycle, (void *)&philo[i]);//&philo[i].thread is the pointer to the thread identifier
		i++;
	}
	i = 0;
	pthread_create(&philo->data->stalker, NULL, ft_osserva, (void *)philo);
	while (i < philo->data->number_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->stalker, NULL);
	return (NULL);
}

void	philo_simulation(t_philo *philo)
{
	ft_start_thread(philo);
	usleep(424242);
	ft_destroyall(philo);
}
