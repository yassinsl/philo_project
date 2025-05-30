/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:01 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 13:50:03 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * get_current_time -Get Current Time in (ms)
 * get_timestamp -Time Has Passed Since The Simulation Started.
 * @time: Struct of Time (in m-seconds and  mc-secand)
 * Return(get_current_time): (time.tv_sc * 1000 + time.tv_usec
	/ 1000) if secceeded
 * Return(get_timestamp) : (get_current_time() - data->start_time) if secceeded
 */

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	get_timestamp(t_data_philosophers *data)
{
	return (get_current_time() - data->start_time);
}
