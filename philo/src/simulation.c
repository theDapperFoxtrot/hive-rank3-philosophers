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

int	start_simulation(t_data *data, t_kotrt *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine, \
			&philos[i]) != 0)
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
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, \
		philos) != 0)
		return (1);
	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}
