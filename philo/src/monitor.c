/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:39 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:40 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// monitor.c
#include "../include/philo.h"

// - Checks a single philosopher's meal time and meal count
// - Returns 1 if philosopher has either died or eaten enough meals
// - Uses mutex locks for thread-safe access to philosopher data
int	check_philosopher_status(t_kotrt *philo, t_data *data)
{
	long	time_since_meal;
	int		meals;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_meal = get_current_time() - philo->last_meal_time;
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (time_since_meal > data->ttd || \
		(data->eat_limit != -1 && meals >= data->eat_limit));
}

// - Handles the death announcement when a philosopher dies
// - Safely updates simulation state using mutex locks
// - Prints death message with proper synchronization
void	handle_philosopher_death(t_kotrt *philo, t_data *data)
{
	pthread_mutex_lock(data->print_mutex);
	if (data->running)
	{
		printf("%ld %d died\n", \
			get_current_time() - data->start_time, philo->id);
		data->running = 0;
	}
	pthread_mutex_unlock(data->print_mutex);
}

// Checks if all philosophers have completed their meal requirements
// Updates simulation state if all philosophers are done eating
// Returns 1 if simulation should stop, 0 otherwise
int	check_meal_completion(t_data *data, int full_count)
{
	if (data->eat_limit != -1 && full_count == data->num_philos)
	{
		pthread_mutex_lock(data->print_mutex);
		if (data->running)
			data->running = 0;
		pthread_mutex_unlock(data->print_mutex);
		return (1);
	}
	return (0);
}

// - Performs one full monitoring cycle for all philosophers
// - Counts philosophers who have eaten enough meals
// - Checks for deaths and meal completion
// - Returns 1 if simulation should stop, 0 otherwise
int	monitor_iteration(t_kotrt *philos, t_data *data)
{
	int	full_count;
	int	i;

	full_count = 0;
	i = 0;
	while (i < data->num_philos)
	{
		if (check_philosopher_status(&philos[i], data))
		{
			if (get_time_since_last_meal(&philos[i]) > data->ttd)
			{
				handle_philosopher_death(&philos[i], data);
				return (1);
			}
			full_count++;
		}
		i++;
	}
	return (check_meal_completion(data, full_count));
}

// - Initializes the data pointers
// - Loops while simulation is running
// - Calls monitor_iteration() for each monitoring cycle
// - Breaks loop if stopping condition is detected
// - Includes a small sleep to reduce CPU usage
void	*monitor_routine(void *arg)
{
	t_kotrt	*philos;
	t_data	*data;

	philos = (t_kotrt *)arg;
	data = philos[0].data;
	while (simulation_running(data))
	{
		if (monitor_iteration(philos, data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
