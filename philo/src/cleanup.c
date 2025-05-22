#include "../include/philo.h"

int	clean_exit(t_kotrt *philos, t_data *data, int exit_code)
{
    int	i;

    // Clean up philosopher resources
    if (philos)
    {
        i = 0;
        while (i < data->num_philos)
        {
            // Destroy last_meal_mutex for each philosopher
            pthread_mutex_destroy(&philos[i].last_meal_mutex);
            i++;
        }
        free(philos);
    }

    // Clean up data resources
    if (data)
    {
        i = 0;
        if (data->forks)
        {
            while (i < data->num_philos)
                pthread_mutex_destroy(&data->forks[i++]);
            free(data->forks);
        }

        if (data->print_mutex)
        {
            pthread_mutex_destroy(data->print_mutex);
            free(data->print_mutex); // Free the malloc'd mutex
        }
    }

    return (exit_code);
}
