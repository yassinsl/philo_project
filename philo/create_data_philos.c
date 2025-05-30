/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_philos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:14:41 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 13:31:26 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * create_philosophers - Create a data structure for the philosophers.
 * @id: id for each philos
 * @last_meal_time: time the last meal each philos
 * Return: Non Return
 */

void	create_philosophers(t_data_philosophers *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philos) * data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->number_of_philosophers;
		data->philos[i].last_meal_time = get_current_time();
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].data = data;
	}
}
