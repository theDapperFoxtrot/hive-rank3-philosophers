#include "../include/philo.h"

void	*philosopher_routine(void *arg)
{
	t_kotrt *philo = (t_kotrt *)arg;
	t_data *data = philo->data;

	while (simulation_running(data))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		print_status(philo, "is eating");
		philo->last_meal_time = get_current_time();
		precise_usleep(data->tte);
		release_forks(philo);
		philo->meals_eaten++;
		pthread_mutex_lock(data->print_mutex);
		if (data->eat_limit > 0 && philo->meals_eaten >= data->eat_limit)
			data->running = 0;
		pthread_mutex_unlock(data->print_mutex);
		print_status(philo, "is sleeping");
		precise_usleep(data->tts);
	}
	return (NULL);
}

void	take_forks(t_kotrt *philo)
{
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    } else {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
}

void release_forks(t_kotrt *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void assign_forks(t_data *data, t_kotrt *philos)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (i % 2 == 0) {
			philos[i].left_fork = &data->forks[i];
			philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		} else {
			philos[i].right_fork = &data->forks[i];
			philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		}
		i++;
	}
}