#include "philo.h"

void print_status_with_time(t_philo *philo, t_status status)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long timestamp_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    const char *status_strings[] = {
        "got fork 1",
        "got fork 2",
        "is eating",
        "is sleeping",
        "is thinking",
        "died"
    };

    printf("[%lld] Philosopher %d %s\n", timestamp_ms, philo->id, status_strings[status]);
}


void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

// bool	has_simulation_stopped(t_table *table)
// {
// 	bool	r;

// 	r = false;
// 	pthread_mutex_lock(&table->sim_stop_lock);
// 	if (table->sim_stop == true)
// 		r = true;
// 	pthread_mutex_unlock(&table->sim_stop_lock);
// 	return (r);
// }



// static void	set_sim_stop_flag(t_table *table, bool state)
// {
// 	pthread_mutex_lock(&table->sim_stop_lock);
// 		table->sim_stop = state;
// 	pthread_mutex_unlock(&table->sim_stop_lock);
// }


// static bool	kill_philo(t_philo *philo)
// {
// 	time_t	time;

// 	time = get_time_in_ms();
// 	if ((time - philo->last_meal) >= philo->table->time_to_die)
// 	{
// 		set_sim_stop_flag(philo->table, true);
// 		print_status_with_time(philo, DIED);
// 		pthread_mutex_unlock(&philo->meal_time_lock);
// 		return (true);
// 	}
// 	return (false);
// }

// static bool	end_condition_reached(t_table *table)
// {
// 	unsigned int	i;
// 	bool			all_ate_enough;

// 	all_ate_enough = true;
// 	i = 0;
// 	while (i < table->nb_philos)
// 	{
// 		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
// 		if (kill_philo(table->philos[i]))
// 			return (true);
// 		if (table->must_eat_count != -1)
// 			if (table->philos[i]->times_ate
// 				< (unsigned int)table->must_eat_count)
// 				all_ate_enough = false;
// 		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
// 		i++;
// 	}
// 	if (table->must_eat_count != -1 && all_ate_enough == true)
// 	{
// 		set_sim_stop_flag(table, true);
// 		return (true);
// 	}
// 	return (false);
// }

// void	*grim_reaper(void *data)
// {
// 	t_table			*table;

// 	table = (t_table *)data;
// 	if (table->must_eat_count == 0)
// 		return (NULL);
// 	set_sim_stop_flag(table, false);
// 	sim_start_delay(table->start_time);
// 	while (true)
// 	{
// 		if (end_condition_reached(table) == true)
// 			return (NULL);
// 		usleep(1000);
// 	}
// 	return (NULL);
// }


int validate_and_initialize_table(int ac, char **av, t_table **table)
{
    if (ac - 1 < 4 || ac - 1 > 5) 
	{
		ft_error();
        return 1;
    }
    if (!is_valid_input(ac, av))
	{
		ft_errorr();
        return 1;
    }
    *table = init_table(ac, av);
    if (!(*table))
	{
		//write(1,"===9",4);
        ft_errorr();
        return 1;
    }
    return 0;
}




// void	philo_sleep(t_table *table, time_t sleep_time)
// {
// 	time_t	wake_up;

// 	wake_up = get_time_in_ms() + sleep_time;
// 	while (get_time_in_ms() < wake_up)
// 	{
// 		if (has_simulation_stopped(table))
// 			break ;
// 		usleep(100);
// 	}
// }

// static void think_routine(t_philo *philo, bool silent)
// {
// 	pthread_mutex_lock(&philo->meal_time_lock);
// 	time_t time_since_last_meal = get_time_in_ms() - philo->last_meal;
// 	time_t time_to_think = (philo->table->time_to_die - time_since_last_meal - philo->table->time_to_eat) / 2;
// 	pthread_mutex_unlock(&philo->meal_time_lock);

// 	time_to_think = time_to_think < 0 ? 0 : time_to_think;
// 	time_to_think = (time_to_think == 0 && silent) ? 1 : time_to_think;
// 	time_to_think = (time_to_think > 600) ? 200 : time_to_think;

// 	if (!silent)
// 		print_status_with_time(philo, THINKING);

// 	philo_sleep(philo->table, time_to_think);
// }



// static void eat_sleep_routine(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
//     pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);

//     print_status_with_time(philo, GOT_FORK_1);
//     print_status_with_time(philo, GOT_FORK_2);
//     print_status_with_time(philo, EATING);

//     pthread_mutex_lock(&philo->meal_time_lock);
//     philo->last_meal = get_time_in_ms();
//     pthread_mutex_unlock(&philo->meal_time_lock);

//     philo_sleep(philo->table, philo->table->time_to_eat);

//     if (!has_simulation_stopped(philo->table))
//     {
//         pthread_mutex_lock(&philo->meal_time_lock);
//         philo->times_ate += 1;
//         pthread_mutex_unlock(&philo->meal_time_lock);
//     }

//     print_status_with_time(philo, SLEEPING);

//     pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
//     pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);

//     philo_sleep(philo->table, philo->table->time_to_sleep);
// }


// static void *lone_philo_routine(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
//     print_status_with_time(philo, GOT_FORK_1);

//     philo_sleep(philo->table, philo->table->time_to_die);

//     print_status_with_time(philo, DIED);
//     pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);

//     return NULL;
// }

time_t get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("\ntv_sec: %ld, tv_usec: %ld\n\n", tv.tv_sec, (long)tv.tv_usec);

    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void synchronize_start(time_t start_time)
{
    while (get_time_in_ms() < start_time)
    {
        printf("Current time: %lld, Start time: %lld\n", (long long)get_time_in_ms(), (long long)start_time);

        // This loop continues as long as the current time is less than the start time.
        // It effectively waits for the start time to be reached before moving on.
    }

    printf("Exiting synchronization loop\n");
}







// void *philosopher(void *data)
// {
// 	write(1,"1PwegwgwrgqrgqergqergqegregeqrheqrhqerherherhwdfdfehwehP", 100);
// 	t_philo *philo = (t_philo *)data;

// 	 pthread_mutex_lock(&philo->meal_time_lock);
// 	 philo->last_meal = philo->table->start_time;
// 	 pthread_mutex_unlock(&philo->meal_time_lock);


// 	sim_start_delay(philo->table->start_time);

// 	// if (philo->table->time_to_die == 0)
// 	// 	return NULL;

// 	// if (philo->table->nb_philos == 1)
// 	// 	return lone_philo_routine(philo);
// 	// else if (philo->id % 2)
// 	// 	think_routine(philo, true);  

// 	// while (!has_simulation_stopped(philo->table))
// 	// {
// 	// 	eat_sleep_routine(philo);
// 	// 	think_routine(philo, false);
// 	// }

// 	 return NULL;
// }



// void *philosopher(void *data)
// {
//     printf("Exin loop\n");
//     t_philo *philo = (t_philo *)data;


//     pthread_mutex_lock(&philo->meal_time_lock);
//     philo->last_meal = philo->table->start_time;
//     pthread_mutex_unlock(&philo->meal_time_lock);

    
//     // Delay the philosopher's start time
//     synchronize_start(philo->table->start_time);

//     // Check if time_to_die is set to 0, if yes, return immediately
//     if (philo->table->time_to_die == 0)
//         return (void *)0;

//     // Handle a single philosopher scenario
//     if (philo->table->nb_philos == 1)
//         return (void *)(intptr_t)lone_philo_routine(philo);

//     // For odd-id philosophers, start by thinking
//     if (philo->id % 2)
//         think_routine(philo, (void *)1);

//     // Continue actions while simulation is ongoing
//     while (!has_simulation_stopped(philo->table))
//     {
//         eat_sleep_routine(philo);
//         think_routine(philo, (void *)0);
//     }

//     return (void *)0;
// }



// int start_simulation(t_table *table)
// {
// 	unsigned int	i;

// 	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
// 	i = 0;
//     printf("Setting start time: %ld\n\n", table->start_time);
// 	 while (i < table->nb_philos)
// 	 {
//          write(1,"78910\n", 7);     
// 	 	if (pthread_create(&table->philos[i]->thread, NULL,
// 	 			&philosopher, table->philos[i]) != 0)
//                 {
//                     write(1,"ABCDE", 5);
//                     ft_errorrrr();
// 	 		        return (-1);
//                 }
// 	 	i++;
// 	}
// 	if (table->nb_philos > 1)
// 	{
// 		if (pthread_create(&table->grim_reaper, NULL,
// 				&grim_reaper, table) != 0)
// 			return (-1);
// 	 }

     
// 	return (0);
// }


int main(int ac, char **av)
{
    t_table *table;

    if (validate_and_initialize_table(ac, av, &table) == 0)
    {
        // Error occurred during validation or initialization
        if (!table)
		    return (-1);
        table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
        printf("Address of table: %p\n", (void *)table);
        printf("Address of philos: %p\n", (void *)table->philos);
        
    }

    else
        {
            write(1,"momo",4);
            return -1;
        }
    // Create philosopher threads here and start the simulation
	//write(1,"ekko",4);
    return 0;
}