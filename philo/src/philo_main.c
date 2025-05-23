/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:45 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:46 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_msg(char *message)
{
	printf("%s\n", message);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_kotrt	*philos;

	if (parse_arguments(argc, argv, &data) == 1)
		return (1);
	if (init_data(&data) == 1)
		return (1);
	philos = init_philosophers(&data);
	if (!philos)
		return (clean_exit(NULL, &data, 1));
	if (start_simulation(&data, philos) == 1)
		return (clean_exit(philos, &data, 1));
	return (clean_exit(philos, &data, 0));
}
