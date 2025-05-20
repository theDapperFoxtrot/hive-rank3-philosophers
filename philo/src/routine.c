#include "../include/philo.h"

void	*philosopher_routine(void *arg)
{
	t_kotrt *philo = (t_kotrt *)arg;
	t_data *data = philo->data;

	// For even/odd starting strategy to prevent deadlock
	if (philo->id % 2 == 0)
		precise_usleep(100);

	while (simulation_running(data))
	{
		// 1. Thinking
		print_status(philo, "is thinking");

		// 2. Take forks
		if (!take_forks(philo))
			break;

		// 3. Eating
		print_status(philo, "is eating");
		philo->last_meal_time = get_current_time();
		precise_usleep(data->tte);
		philo->meals_eaten++;
		pthread_mutex_lock(&data->print_mutex);
		if (data->eat_limit > 0 && philo->meals_eaten >= data->eat_limit)
			data->running = 0;
		pthread_mutex_unlock(&data->print_mutex);

		// 4. Release forks
		release_forks(philo);

		// 5. Sleeping
		print_status(philo, "is sleeping");
		precise_usleep(data->tts);
	}
	return (NULL);
}

int take_forks(t_kotrt *philo)
{
	t_data *data = philo->data;

	// Take left fork
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");

	// Not sure how I feel about this logic
	// // For single philosopher case
	// if (data->num_philos == 1)
	// {
	// 	precise_usleep(data->ttd + 10);
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	return (0);
	// }

	// Take right fork
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");

	return (1);
}

void release_forks(t_kotrt *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}