/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:55:20 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 15:18:32 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * get_data_from_args -Parse the arguments for the philosopher data.
 * check_philo_values -Check Error Value
 * Return: 0 if succeeded or -1
 */
int	check_philo_values(t_data_philosophers *ph)
{
	if (ph->number_of_philosophers == -2)
		return (ft_error_msg(INVALID_NUMBER), -1);
	if (ph->time_to_die == -2)
		return (ft_error_msg(INVALID_NUMBER), -1);
	if (ph->time_to_eat == -2)
		return (ft_error_msg(INVALID_NUMBER), -1);
	if (ph->time_to_sleep == -2)
		return (ft_error_msg(INVALID_NUMBER), -1);
	if (ph->number_of_times_each_philosopher_must_eat == -2)
		return (ft_error_msg(INVALID_NUMBER), -1);
	return (0);
}

int	get_data_from_args(t_data_philosophers *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (check_philo_values(data) == -1)
		return (-1);
	return (0);
}
