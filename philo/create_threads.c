/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:51:53 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/30 11:10:13 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * create_threads - Create Threads For Each Philo
 * @someone_died : number to check if someone diad
 * Return: NONE Return
 */

void	create_threads(t_data_philosophers *data)
{
	int	i;

	data->start_time = get_current_time();
	data->someone_died = 0;
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_create(&data->philos[i].thread, NULL, philo_routine,
			&data->philos[i]);
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	free_resources(data);
}
