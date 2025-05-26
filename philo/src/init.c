/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:36 by smishos           #+#    #+#             */
/*   Updated: 2025/05/26 15:29:20 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	destroy_mutexes(t_data *data, int mutex_count)
{
	int	i;

	i = 0;
	while (i < mutex_count)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	free(data->print_mutex);
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

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

void	fork_assignment(t_kotrt *philos, int i)
{
	if (i % 2 == 0)
	{
		philos[i].left_fork = &philos->data->forks[i];
		philos[i].right_fork = \
			&philos->data->forks[(i + 1) % philos->data->num_philos];
	}
	else
	{
		philos[i].right_fork = &philos->data->forks[i];
		philos[i].left_fork = \
			&philos->data->forks[(i + 1) % philos->data->num_philos];
	}
}

t_kotrt	*init_philosophers(t_data *data)
{
	int		i;
	t_kotrt	*philos;

	philos = malloc(sizeof(t_kotrt) * data->num_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = data->start_time;
		if (pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
			clean_exit(philos, data, 1);
		philos[i].data = data;
		fork_assignment(philos, i);
		i++;
	}
	return (philos);
}
