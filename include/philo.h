/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:07:41 by smishos           #+#    #+#             */
/*   Updated: 2025/03/26 15:04:56 by smishos          ###   ########.fr       */
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

typedef struct s_philo
{
	int							argc;
	char						**argv;
	// int						n_philo;
	// int						p_index;
	// int						eaten;
	// int						*died;
	// long long				die_time;
	// long long				eat_time;
	// long long				sleep_time;
	// pthread_t				thread;
	// pthread_mutex_t			*left_fork;
	// pthread_mutex_t			*right_fork;
	// struct s_main_struct		*back;
	// long long				start_time;
	// long long				last_meal;
}	t_philo;

#endif