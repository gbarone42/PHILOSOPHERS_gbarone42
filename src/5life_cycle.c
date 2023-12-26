#include "../includes/philosophers.h"

void	init_last_meal_time(t_philo *philo)
{
	if (philo->time_last_meal == 0)
		philo->time_last_meal = ft_get_time_now();
}

int	is_simulation_over(t_data *data)
{
	return (data->all_satisfied || death_status(data));
}

//starting routine for a thread
//using the pthreads library, thread functions must have this signature:
//returning void* and taking a single void* argument.
void	pick_up_and_put_down_forks(t_philo *philo)
{
	usleep(1000);
    // Philosophers pick up forks based on their ID to prevent deadlock.
	if (philo->id_philo % 2 == 0)
	{  // Even ID philosopher picks up right fork first.
		pthread_mutex_lock(&philo->data->forks[philo->fk2]);
		pthread_mutex_lock(&philo->data->forks[philo->fk1]);
	}
	else
	{  // Odd ID philosopher picks up left fork first.
		pthread_mutex_lock(&philo->data->forks[philo->fk1]);
		pthread_mutex_lock(&philo->data->forks[philo->fk2]);
	}
    // Attempt to eat
	ft_eat(philo);
    // Put down the forks after eating or if eating was not successful.
	pthread_mutex_unlock(&philo->data->forks[philo->fk1]);
	pthread_mutex_unlock(&philo->data->forks[philo->fk2]);
}

// Function for the philosopher's life cycle
void	*life_cycle(void *ph)
{
	t_philo *philo;

    philo = (t_philo *)ph;
	init_last_meal_time(philo);
	while (!is_simulation_over(philo->data))
	{
		if (philo->id_philo % 2 == 0)
		{
			usleep(942);// Delay for even ID philosophers
		}
		pick_up_and_put_down_forks(philo);
		if (is_simulation_over(philo->data))
			break ;
		if (ft_sleep(philo) != SUCCESS)
			break ;
		ft_think(philo);
	}
	return (NULL);// End of the philosopher's life cycle
}

// void *life_cycle(void *ph)
// {
//     t_philo *philo = (t_philo *)ph;

//     init_last_meal_time(philo);
//     while (!is_simulation_over(philo->data))
// 	{
//         if (ft_eat(philo) != SUCCESS)
// 		{
//             break; // Break the loop if eating failed or death occurred
//         }
//         if (is_simulation_over(philo->data))
// 		{
//             break;
//         }
//         if (ft_sleep(philo) != SUCCESS)
// 		{
//             break; // Break the loop if sleeping failed or death occurred
//         }
//         ft_think(philo);
//     }
//     return NULL; // End of the philosopher's life cycle
// }
