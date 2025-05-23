#include "../include/philo.h"

int	bring_out_your_dead(t_kotrt *philos, t_data *data, int i)
{
	if (get_time_since_last_meal(&philos[i]) > data->ttd)
	{
		pthread_mutex_lock(data->print_mutex);
		print_death(&philos[i]);
		data->running = 0;
		pthread_mutex_unlock(data->print_mutex);
		return (1);
	}
	return (0);
}

int	yall_eat_yet(t_data *data, int full_count)
{
	if (full_count == data->num_philos)
	{
		pthread_mutex_lock(data->print_mutex);
		data->running = 0;
		pthread_mutex_unlock(data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_kotrt	*philos;
	t_data	*data;
	int		full_count;
	int		i;

	philos = (t_kotrt *)arg;
	data = philos[0].data;
	while (simulation_running(data))
	{
		full_count = 0;
		i = 0;
		while (i < data->num_philos)
		{
			if (bring_out_your_dead(philos, data, i))
				return (NULL);
			if (data->eat_limit > 0 && philos[i].meals_eaten >= data->eat_limit)
				full_count++;
			i++;
		}
		if (yall_eat_yet(data, full_count))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
