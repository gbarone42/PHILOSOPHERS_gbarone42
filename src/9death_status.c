#include "../includes/philosophers.h"

int	death_status(t_data *data)
{
    int is_dead;

    pthread_mutex_lock(&data->dad);// important for thread safety to ensure that no other thread can access the shared resource (in this case, the dead field in t_data) at the same time.
    is_dead = (data->dead == 1);//The result of this comparison is a boolean value: true if data->dead is 1, and false otherwise.
    pthread_mutex_unlock(&data->dad);//The mutex should be unlocked as soon as the critical section (protected data) is no longer being accessed to avoid deadlocks and ensure good concurrency performance.

    return is_dead;//either 1 or 0
}


//mutex ensures that the check is performed without interference from 
//other threads, maintaining the consistency and reliability of the 
//shared dead state.