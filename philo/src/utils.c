#include "../include/philo.h"

// Thread-safe status printing
void	print_status(t_kotrt *philo, char *status)
{
	pthread_mutex_lock(philo->data->print_mutex);
	if (philo->data->running)
		printf("%ld %d %s\n", \
			get_current_time() - philo->data->start_time, \
			philo->id, status);
	pthread_mutex_unlock(philo->data->print_mutex);
}

// Special print for death to ensure it shows immediately
void	print_death(t_kotrt *philo)
{
	printf("%ld %d died\n", \
		get_current_time() - philo->data->start_time, \
		philo->id);
}

// Precise timing functions
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(t_kotrt *philo, long milliseconds)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < milliseconds)
	{
		if (simulation_running(philo->data) == 0)
			return ;
		usleep(500);
	}
}

long	get_time_since_last_meal(t_kotrt *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last_meal = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (time_since_last_meal);
}
