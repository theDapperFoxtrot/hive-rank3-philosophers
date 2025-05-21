#include "../include/philo.h"

int destroy_mutexes(t_data *data, int mutex_count)
{
	int i;

	i = 0;
	while (i < mutex_count)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	return (1);
}

int	init_data(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
    if (!data->print_mutex)
    {
        free(data->forks);
        return (1);
    }
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_mutexes(data, i));
		i++;
	}
	if (pthread_mutex_init(data->print_mutex, NULL) != 0)
		return (destroy_mutexes(data, data->num_philos));
	data->running = 1;
	data->start_time = get_current_time();
	return (0);
}

t_kotrt *init_philosophers(t_data *data)
{
	int i;

	t_kotrt *philos = malloc(sizeof(t_kotrt) * data->num_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = data->start_time;
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		philos[i].data = data;

		// To avoid deadlock: alternate fork picking order
		// if (i % 2 == 0)
		// {
			philos[i].left_fork = &data->forks[i];
			philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		// }
		// else
		// {
			// philos[i].right_fork = &data->forks[i];
			// philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		// }
		i++;
	}
	return (philos);
}
