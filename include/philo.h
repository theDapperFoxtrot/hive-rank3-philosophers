/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:07:41 by smishos           #+#    #+#             */
/*   Updated: 2025/04/20 14:52:07 by smishos          ###   ########.fr       */
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

// # define FORK		"has taken a fork"
// # define EAT		"is eating"
// # define SLEEP		"is sleeping"
// # define THINK		"is thinking"
// # define DIED		"died"
// # define ERROR		"Error"
// # define SUCCESS	"Success"
// # define MALLOC_ERR	"Malloc error"
// # define ARG_ERR	"Argument error"
// # define TIME_ERR	"Time error"
// # define THREAD_ERR	"Thread error"
// # define USLEEP_ERR	"Usleep error"
// # define TIMEOUT_ERR	"Timeout error"
// # define TIMEOUT	"Timeout"
// # define MAX_PHILO	200
// # define MAX_FORK	200
// # define MAX_EAT	200
// # define MAX_SLEEP	200
// # define MAX_DIE	200
// # define MAX_ARG	5
// # define MAX_TIME	2000000000
// # define MIN_TIME	0
# define PHILOS	10

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