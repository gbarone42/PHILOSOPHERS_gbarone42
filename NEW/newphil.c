#include "philo.h"

int main(int ac, char **av)
{
    t_table *table;

    if (ac - 1 < 4 || ac - 1 > 5) 
	{
		ft_error();
	    // Print error message about invalid number of arguments
        return 1;
    }

    if (!is_valid_input(ac, av))
	{
		ft_errorr();
        // Print error message about invalid input
        return 1;
    }

    table = init_table(ac, av, 1);
    if (!table) {
        // Print error message about table initialization failure
        return 1;
    }

    // Create philosopher threads here and start the simulation

    return 0;
}