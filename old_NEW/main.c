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



int validate_and_initialize_table(int ac, char **av, t_table **table)
{
    if (ac - 1 < 4 || ac - 1 > 5) 
	{
		ft_error();
        return 1;
    }
    if (!is_valid_input(ac, av))
	{
		ft_errorrrr();
        return 1;
    }
    *table = init_table(ac, av);
    if (!(*table))
	{
		write(1,"===9",4);
        ft_errorr();
        return 1;
    }
    return 0;
}

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



void do_threads(t_table *table) {
    int i;

    i = 0;
    // while (i < table->nb_philos)
    // {
    //     pthread_create(&(table->philos[i].id_thread),
    //                    NULL, &do_philo, &(table->philos[i]));
    //     i++;
    // }
    printf("sausage");
    i = 0;
    while (i < table->nb_philos) {
        pthread_join(table->philos[i]->id_thread, NULL);
        i++;
    }
}


int main(int ac, char **av) {
    t_table *table;

    if (validate_and_initialize_table(ac, av, &table) == 0) {
        // Error occurred during validation or initialization
        if (!table)
            return -1;   
        table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
        printf("Address of table: %p\n", (void *)table);
        printf("Address of philos: %p\n", (void *)table->philos);
        do_threads(table);
    }
    // Create philosopher threads here and start the simulation
    //write(1,"ekko",4);
    return 0;
}
