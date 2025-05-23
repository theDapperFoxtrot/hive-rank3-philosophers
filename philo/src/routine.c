/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:48 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:49 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(t_kotrt *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	while (simulation_running(data))
		usleep(1000);
	return (NULL);
}

void	philosopher_routine_running(t_kotrt *philo, t_data *data)
{
	while (simulation_running(data))
	{
		if (!simulation_running(data))
			return ;
		print_status(philo, "is thinking");
		take_forks(philo);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		precise_usleep(philo, data->tte);
		release_forks(philo);
		philo->meals_eaten++;
		print_status(philo, "is sleeping");
		precise_usleep(philo, data->tts);
		usleep(500);
	}
}

void	*philosopher_routine(void *arg)
{
	t_kotrt	*philo;
	t_data	*data;

	philo = (t_kotrt *)arg;
	data = philo->data;
	if (data->num_philos == 1)
		return (one_philo(philo, data));
	if (philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		usleep(5000);
	}
	philosopher_routine_running(philo, data);
	return (NULL);
}

void	take_forks(t_kotrt *philo)
{
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

void	release_forks(t_kotrt *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
