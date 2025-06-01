/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:01:42 by smishos           #+#    #+#             */
/*   Updated: 2025/05/23 20:01:43 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// - Validates argument count (4-5 args + program name)
// - Parses arguments into data structure
// - Handles optional meal limit argument
// - Validates all values are positive integers
// - Returns error message for invalid input
int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error_msg("Error: Wrong number of arguments"));
	data->num_philos = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	data->eat_limit = -1;
	if (argc == 6)
		data->eat_limit = ft_atoi(argv[5]);
	if (data->num_philos <= 0 || \
	data->ttd <= 0 || \
	data->tte <= 0 || \
	data->tts <= 0 || \
	(argc == 6 && data->eat_limit <= 0))
		return (error_msg("Error: Invalid arg values"));
	return (0);
}
