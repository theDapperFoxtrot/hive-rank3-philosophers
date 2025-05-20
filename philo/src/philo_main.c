#include "../include/philo.h"

int error_msg(char *message)
{
	printf("%s\n", message);
	return (1);
}


int destroy_mutexes(t_data *data, int mutex_count)
{
	int i;

	i = 0;
	while (i < mutex_count)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	return (1);
}

void precise_usleep(long milliseconds)
{
	long start = get_current_time();
	while (get_current_time() - start < milliseconds)
		usleep(500);
}

void *philosopher_routine(void *arg)
{
	t_kotrt *philo = (t_kotrt *) arg;

	while (simulation_running(philo->data))
	{
		// THINKING PHASE (includes waiting for forks)
		print_status(philo, "is thinking");

		// Attempt to take forks - blocks until available
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);

		// EATING PHASE
		print_status(philo, "is eating");
		precise_usleep(philo->data->tte);

		// Release forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// SLEEPING PHASE
		print_status(philo, "is sleeping");
		precise_usleep(philo->data->tts);
	}
	return (NULL);
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
		philos[i].data = data;

		// Assign forks (left and right)
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (philos);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_kotrt *philos;

	if (parse_arguments(argc, argv, &data) == 1)
		return (1);

	if (init_data(&data) == 1)
		return (1);

	philos = init_philosophers(&data);
	if (!philos)
		return (clean_exit(NULL, &data, 1));

	if (start_simulation(&data, philos) == 1)
		return (clean_exit(philos, &data, 1));

	return (clean_exit(philos, &data, 0));
}
