#include "../include/philo.h"

int	start_simulation(t_data *data, t_kotrt *philos)
{
	int	i;
	i = 0;
	// Create philosopher threads
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	// Create monitor thread
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, philos) != 0)
		return (1);
	i = 0;
	// Wait for threads to finish
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	return (0);
}
