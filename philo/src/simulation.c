#include "../include/philo.h"

int start_simulation(t_data *data, t_philo *philos)
{
    // Create philosopher threads
    for (int i = 0; i < data->num_philos; i++)
    {
        if (pthread_create(&philos[i].thread, NULL, 
            philosopher_routine, &philos[i]) != 0)
            return (1);
    }
    
    // Create monitor thread
    if (pthread_create(&data->monitor_thread, NULL, 
        monitor_routine, philos) != 0)
        return (1);
    
    // Wait for threads to finish
    for (int i = 0; i < data->num_philos; i++)
        pthread_join(philos[i].thread, NULL);
    
    pthread_join(data->monitor_thread, NULL);
    
    return (0);
}