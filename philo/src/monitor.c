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

#include "../include/philo.h"

int	bring_out_your_dead(t_kotrt *philos)
{
    time_t	time_since_meal;
    int	meals;

    pthread_mutex_lock(&philos->last_meal_mutex);  // Lock before reading both values
    time_since_meal = get_current_time() - philos->last_meal_time;
    meals = philos->meals_eaten;
    pthread_mutex_unlock(&philos->last_meal_mutex);  // Unlock after reading

    if (time_since_meal > philos->data->ttd)
        return (1);
    if (philos->meals_eaten != -1 && meals >= philos->meals_eaten)
        return (1);
    return (0);
}

int	yall_eat_yet(t_data *data, int full_count)
{
	if (full_count == data->num_philos)
	{
		pthread_mutex_lock(data->print_mutex);
		data->running = 0;
		pthread_mutex_unlock(data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_kotrt	*philos;
	t_data	*data;
	int		full_count;
	int		i;

	philos = (t_kotrt *)arg;
	data = philos[0].data;
	while (simulation_running(data))
	{
		full_count = 0;
		i = 0;
		while (i < data->num_philos)
		{
			if (bring_out_your_dead(philos))
				return (NULL);
			if (data->eat_limit > 0 && philos[i].meals_eaten >= data->eat_limit)
				full_count++;
			i++;
		}
		if (yall_eat_yet(data, full_count))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
