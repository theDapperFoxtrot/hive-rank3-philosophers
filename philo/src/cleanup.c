/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:31 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:32 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_philo(t_kotrt *philos, t_data *data)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&philos[i].last_meal_mutex);
			i++;
		}
		free(philos);
	}
}

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->print_mutex)
	{
		pthread_mutex_destroy(data->print_mutex);
		free(data->print_mutex);
	}
}

int	clean_exit(t_kotrt *philos, t_data *data, int exit_code)
{
	if (philos)
		clean_philo(philos, data);
	if (data)
		clean_data(data);
	return (exit_code);
}
