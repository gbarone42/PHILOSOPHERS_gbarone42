
#include "../includes/philosophers.h"

void	ft_stampa_pd(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (death_status(philo->data) == 1 || philo->data->all_satisfied == 1)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%llu %d %s\n",
		delta_time(philo->data->time_start), philo->id_philo, str);
	usleep(5);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int ft_eat(t_philo *philo)
{
    // Check for death before attempting to eat
    if (death_status(philo->data) == 1)
        return DEATH_OCCURRED;

    // Locking the forks would typically happen here

    ft_stampa_pd(philo, "took a chopstick");
    ft_stampa_pd(philo, "took both chopsticks 🥢");
    
    // Additional death check here could be beneficial
    if (death_status(philo->data) == 1)
        return DEATH_OCCURRED;

    philo->burpo += 1;
    ft_stampa_pd(philo, "is eating🍗");
    usleep(philo->data->time_to_eat * 1000);

    // Update the last meal time only if the philosopher is still alive
    pthread_mutex_lock(&philo->data->last_meal_mutex);
    if (death_status(philo->data) == 0) {
        philo->time_last_meal = ft_get_time_now();
    }
    pthread_mutex_unlock(&philo->data->last_meal_mutex);

    return SUCCESS;
}

// int ft_eat(t_philo *philo) {
//     if (death_status(philo->data) == 1)
//         return DEATH_OCCURRED; // You need to define DEATH_OCCURRED as a constant, e.g., -1

//     pthread_mutex_lock(&philo->data->forks[fk_lock_1(philo->fk1, philo->fk2)]);
//     pthread_mutex_lock(&philo->data->forks[fk_lock_2(philo->fk1, philo->fk2)]);
//     ft_stampa_pd(philo, "ha preso la sua forchetta 🍴");
//     ft_stampa_pd(philo, "ha preso la forchetta di un altro 🍴");
//     philo->burpo += 1;
//     ft_stampa_pd(philo, "sta mangiando!🍝");
//     usleep(philo->data->time_to_eat * 1000);

//     pthread_mutex_lock(&philo->data->last_meal_mutex);
//     philo->time_last_meal = ft_get_time_now();
//     pthread_mutex_unlock(&philo->data->last_meal_mutex);

//     pthread_mutex_unlock(&philo->data->forks[fk_lock_1(philo->fk1, philo->fk2)]);
//     pthread_mutex_unlock(&philo->data->forks[fk_lock_2(philo->fk1, philo->fk2)]);
    
//     return SUCCESS;
// }

int ft_sleep(t_philo *philo)
{
    if (death_status(philo->data) == 1)
        return DEATH_OCCURRED;

    ft_stampa_pd(philo, "is sleepin 🌙");
    usleep(philo->data->time_to_sleep * 1000);
    
    return SUCCESS;
}

void	ft_think(t_philo *philo)
{
	if (death_status(philo->data) == 1)
		return ;
	ft_stampa_pd(philo, "is thinkin..");
}
