/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:52:34 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 14:55:34 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * free_resources - free all resource
 * Return: NON Return
 */

void	free_resources(t_data_philosophers *philos)
{
	int	i;

	if (philos)
	{
		i = -1;
		while (++i < philos->number_of_philosophers)
			pthread_mutex_destroy(&philos->forks[i]);
		pthread_mutex_destroy(philos->print_mutex);
		pthread_mutex_destroy(philos->death_mutex);
		free(philos->forks);
		free(philos->print_mutex);
		free(philos->death_mutex);
		free(philos->philos);
	}
}
