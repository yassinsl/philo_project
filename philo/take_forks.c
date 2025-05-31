/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:06:34 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/31 11:08:31 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static int	lock_first_fork(t_philos *philo, int first)
{
	pthread_mutex_lock(&philo->data->forks[first]);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[first]);
		return (-1);
	}
	print_status(philo, TAKE_FORK);
	return (0);
}

static int	lock_second_fork(t_philos *philo, int first, int second)
{
	pthread_mutex_lock(&philo->data->forks[second]);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[first]);
		pthread_mutex_unlock(&philo->data->forks[second]);
		return (-1);
	}
	print_status(philo, TAKE_FORK);
	return (0);
}

int	take_forks(t_philos *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (lock_first_fork(philo, first_fork) == -1)
		return (-1);
	return (lock_second_fork(philo, first_fork, second_fork));
}
