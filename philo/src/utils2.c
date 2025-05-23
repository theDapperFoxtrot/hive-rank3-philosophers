/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:57 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:58 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	simulation_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(data->print_mutex);
	running = data->running;
	pthread_mutex_unlock(data->print_mutex);
	return (running);
}
