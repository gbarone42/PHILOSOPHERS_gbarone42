#include "../includes/philosophers.h"

// The ft_is_dead function should be responsible for
// checking if a philosopher has died. This function
// would typically compare the time since the philosopher's 
// last meal to the time_to_die parameter.
// If the time elapsed since the last meal is greater than time_to_die,
// the philosopher is considered dead.

int ft_is_dead(t_philo *philo)
{
    long long dead_time;       // Declaration of dead_time.
    long long current_time;    // Declaration of current_time.
    int ret;                   // Declaration of ret.

    // Assignment of dead_time.
    // Storing the maximum time a philosopher can go without eating.
    dead_time = (long long)philo->data->time_to_die;

    // Consolidating mutex lock, time retrieval, and mutex unlock.
    // Locks the mutex before accessing the shared timestamp.
    pthread_mutex_lock(&philo->data->timestamp_mutex);
    // Gets the current time.
    current_time = ft_get_time_now();  
    // Unlocks the mutex after accessing the shared timestamp. 
    // This ensures thread-safe access to shared data.
    pthread_mutex_unlock(&philo->data->timestamp_mutex);
    // Lock and check in a single block to minimize locked duration.
    // Locks the mutex before accessing the philosopher's last meal time.
    pthread_mutex_lock(&philo->data->last_meal_mutex);
    // Determines if the philosopher is dead based on the last meal time and current time.
    ret = ft_ca(philo, dead_time, current_time);  
    // Always unlock after checking.
    pthread_mutex_unlock(&philo->data->last_meal_mutex);  

    // Returns the result of the death check.
    return ret;
}

int ft_sazio(t_philo *philo) {
    if (philo->data->number_of_meals <= 0) {
        return 0; // No meal limit set.
    }

    int satisfied_count = 0;
    for (int i = 0; i < philo->data->number_of_philos; i++) {
        // Protect with mutex if philo[i].burpo is accessed by multiple threads
        if (philo[i].burpo >= philo->data->number_of_meals) {
            satisfied_count++;
        }
    }

    if (satisfied_count == philo->data->number_of_philos) {
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%llu 🌈 GENERAL SATISFACTION\n", delta_time(philo->data->time_start));
        philo->data->all_satisfied = 1;
        pthread_mutex_unlock(&philo->data->print_mutex);
        return 1;
    }
    return 0;
}

void *ft_osserva(void *ph) {
    t_philo *philo = (t_philo *)ph;

    while (1) {
        if (ft_is_dead(philo) || (philo->data->number_of_meals > 0 && ft_sazio(philo))) {
            break;
        }
        usleep(1000); // Check every 1 millisecond
    }
    return NULL;
}