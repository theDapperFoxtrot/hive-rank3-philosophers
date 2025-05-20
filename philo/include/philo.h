/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:07:41 by smishos           #+#    #+#             */
/*   Updated: 2025/05/20 16:25:50 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <unistd.h> //usleep
# include <stdlib.h> //malloc, free, write
# include <string.h> //memset
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include "../libft/libft.h"

typedef struct  s_data
{
	int							num_philos;
	int							ttd;
	int							tte;
	int							tts;
	int							eat_limit;
	long						start_time;
	int							running;
	pthread_mutex_t				*forks;
	pthread_mutex_t				*print_message;
	pthread_t					monitor_thread;
}							t_data;

typedef struct s_kotrt
{
	int							id;
	pthread_t					thread;
	long						last_meal_time;
	int							meals_eaten;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	t_data						*data;
}							t_kotrt;

int	parse_arguments(int argc, char **argv, t_data *data);
int	init_data(t_data *data);

#endif