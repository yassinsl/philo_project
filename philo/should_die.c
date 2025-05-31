/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:09:51 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/31 11:31:01 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_usleep(int duration, t_philos *philos)
{
	long	start;

	start = get_current_time();
	while (!should_stop(philos))
	{
		if (get_current_time() - start >= duration)
			break ;
		usleep(100);
	}
}

void	unlock_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

bool	should_stop(t_philos *philo)
{
	bool	stop;

	pthread_mutex_lock(philo->data->death_mutex);
	stop = philo->data->someone_died;
	pthread_mutex_unlock(philo->data->death_mutex);
	return (stop);
}
