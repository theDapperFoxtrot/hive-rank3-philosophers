#include "../include/philo.h"

void *monitor_routine(void *arg)
{
	t_kotrt *philos = (t_kotrt *)arg;
	t_data *data = philos[0].data;
	int full_count;

	while (simulation_running(data))
	{
		full_count = 0;
		for (int i = 0; i < data->num_philos; i++)
		{
			// Check starvation
			if (get_time_since_last_meal(&philos[i]) > data->ttd)
			{
				print_death(&philos[i]);
				pthread_mutex_lock(&data->print_mutex);
				data->running = 0;
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			// Check meal completion
			if (data->eat_limit > 0 && philos[i].meals_eaten >= data->eat_limit)
				full_count++;
		}
		// All philosophers have eaten enough
		if (full_count == data->num_philos)
		{
			pthread_mutex_lock(&data->print_mutex);
			data->running = 0;
			pthread_mutex_unlock(&data->print_mutex);
			return (NULL);
		}
		// Small delay to prevent busy waiting
		usleep(1000);
	}
	return (NULL);
}
