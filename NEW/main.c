#include "philo.h"


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

int main(int ac, char **av)
{
    t_table *table;

    if (validate_and_initialize_table(ac, av, &table) != 0)
    {
        // Error occurred during validation or initialization
        return 1;
    }

    // Create philosopher threads here and start the simulation
	//write(1,"ekko",4);
    return 0;
}