#include "../include/philo.h"

int	init_data(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_mutexes(data, i));
		i++;
	}
	if (pthread_mutex_init(&data->print_message, NULL) != 0)
		return (destroy_mutexes(data, data->num_philos));
	data->running = 1;
	data->start_time = get_current_time();
	return (0);
}
