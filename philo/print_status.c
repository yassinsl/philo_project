/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:56:23 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/31 11:35:54 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * print_status - Print status for each philos
 * Return: NON Return
 */
void	print_status(t_philos *philo, char *msg)
{
	pthread_mutex_lock(philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", get_timestamp(philo->data), philo->id, msg);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	pthread_mutex_unlock(philo->data->death_mutex);
}
