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
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
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
