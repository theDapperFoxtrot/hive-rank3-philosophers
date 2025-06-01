/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:51 by smishos           #+#    #+#             */
/*   Updated: 2025/05/26 15:27:14 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Creates threads for all philosophers
int	create_philosopher_threads(t_data *data, t_kotrt *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, \
			philosopher_routine, &philos[i]) != 0)
		{
			while (i > 0)
			{
				pthread_join(philos[i - 1].thread, NULL);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

// Creates the monitor thread
int	create_monitor_thread(t_data *data, t_kotrt *philos)
{
	if (pthread_create(&data->monitor_thread, \
		NULL, monitor_routine, philos) != 0)
		return (1);
	return (0);
}

// Waits for all threads to finish (monitor first, then philosophers)
void	join_all_threads(t_data *data, t_kotrt *philos)
{
	int	i;

	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

// Main simulation starter using helper functions
int	start_simulation(t_data *data, t_kotrt *philos)
{
	if (create_philosopher_threads(data, philos) != 0)
		return (1);
	if (create_monitor_thread(data, philos) != 0)
		return (1);
	join_all_threads(data, philos);
	return (0);
}
