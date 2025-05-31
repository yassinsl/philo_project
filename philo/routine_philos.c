/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:58 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/31 11:33:40 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * philo_routine -Create Philo Routine
 * take_forks -locks the two mutexes representing the philosopher's
		left and right forks to safely pick them up before eating.
 * philos_eat - simulates a philosopher picking up forks, eating for a set time,
	then releasing the forks.
 * Return(philos_routine): NULL if secceeded
 * Return(take_fork philos_eat) : 0 success, -1 failure
 */

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->data->death_mutex);
	print_status(philo, EAT_MSG);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	if (!should_stop(philo))
	{
		pthread_mutex_lock(philo->data->death_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->data->death_mutex);
	}
}

void	one_philos(t_philos *philos)
{
	print_status(philos, TAKE_FORK);
	usleep(philos->data->time_to_die * 1000);
	print_status(philos, IS_DEAD_MSG);
}

static void	philo_think(t_philos *philo)
{
	long	time_since_meal;
	long	time_left;
	long	think_time;

	if (philo->data->number_of_philosophers % 2)
	{
		pthread_mutex_lock(philo->data->death_mutex);
		time_since_meal = get_current_time() - philo->last_meal_time;
		time_left = philo->data->time_to_die - time_since_meal;
		pthread_mutex_unlock(philo->data->death_mutex);
		if (time_left > 0)
		{
			think_time = (long)(time_left * 0.9);
			if (think_time > 0)
				ft_usleep(think_time, philo);
		}
	}
}

static void	*philo_execute_loop(t_philos *philo)
{
	int	a;

	while (1)
	{
		pthread_mutex_lock(philo->data->death_mutex);
		a = philo->data->number_of_times_each_philosopher_must_eat;
		if (philo->data->number_of_times_each_philosopher_must_eat != -1
			&& philo->meals_eaten >= a)
			return (pthread_mutex_unlock(philo->data->death_mutex), NULL);
		pthread_mutex_unlock(philo->data->death_mutex);
		if (take_forks(philo) == -1)
			return (unlock_forks(philo), NULL);
		philo_eat(philo);
		if (should_stop(philo))
			return (NULL);
		print_status(philo, SLEEP_MSG);
		ft_usleep(philo->data->time_to_sleep, philo);
		if (should_stop(philo))
			return (NULL);
		print_status(philo, THINK_MSG);
		philo_think(philo);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(1500);
	if (philo->data->number_of_philosophers == 1)
		return (one_philos(philo), NULL);
	return (philo_execute_loop(philo));
}
