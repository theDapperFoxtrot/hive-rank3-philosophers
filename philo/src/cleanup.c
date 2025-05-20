#include "../include/philo.h"

int	clean_exit(t_kotrt *philos, t_data *data, int exit_code)
{
	int	i;

	if (philos)
		free(philos);

	i = 0;
	if (data->forks)
	{
		for (int i = 0; i < data->num_philos; i++)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}

	pthread_mutex_destroy(&data->print_mutex);
	return (exit_code);
}
