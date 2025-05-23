#include "../include/philo.h"

int	simulation_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(data->print_mutex);
	running = data->running;
	pthread_mutex_unlock(data->print_mutex);
	return (running);
}
