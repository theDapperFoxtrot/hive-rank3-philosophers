#include "../include/philo.h"

void	*philosopher_routine(void *arg)
{
	t_kotrt *philo = (t_kotrt *)arg;
	t_data *data = philo->data;

	// Add a special case for single philosopher
    if (data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_unlock(philo->left_fork);
        // Wait for death without trying to eat
        while (simulation_running(data))
            usleep(1000);
        return NULL;
    }

	while (simulation_running(data))
	{
		if (!simulation_running(data))
			break;
		print_status(philo, "is thinking");
		take_forks(philo);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		precise_usleep(data->tte);
		release_forks(philo);
		philo->meals_eaten++;
		print_status(philo, "is sleeping");
		precise_usleep(data->tts);
	}
	return (NULL);
}

void	take_forks(t_kotrt *philo)
{
    // Always take lower-numbered fork first
    if (philo->left_fork < philo->right_fork)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
}

void release_forks(t_kotrt *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
