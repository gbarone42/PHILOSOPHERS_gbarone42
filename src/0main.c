#include "../includes/philosophers.h"


int main(int ac, char **av)
{
    t_data *data;
    t_philo *philo;

    if (!check(ac, av))
        return (0);
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    philo = malloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
    ft_general_init(ac, av, data, philo);
    if (data->number_of_philos > 1)
		philo_simulation(philo); 
    else
        ft_lonely_boy(philo);
    return (0);
}