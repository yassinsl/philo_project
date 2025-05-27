/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:58 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 15:12:43 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * philo_routine -Create Philo Routine
 * take_forks
	-locks the two mutexes representing the philosopher’s
		left and right forks to safely pick them up before eating.
 * philos_eat - simulates a philosopher picking up forks, eating for a set time,
	then releasing the forks.
 * Return(philos_routine): NULL if secceeded
 * Rrturn(take_fork philos_eat) : NON Return
 */
void	take_forks(t_philos *philo)
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
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, TAKE_FORK);
}

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->data->death_mutex);
	print_status(philo, EAT_MSG);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->data->death_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	one_philos(t_philos *philos)
{
	print_status(philos, "has taken a fork");
	usleep(philos->data->time_to_die * 1000);
	print_status(philos, "is dead");
	philos->data->someone_died = 1;
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (philo->id % 2)
		usleep(1500);
	if (philo->data->number_of_philosophers == 1)
		return (one_philos(philo), NULL);
	while (!philo->data->someone_died)
	{
		take_forks(philo);
		philo_eat(philo);
		print_status(philo, SLEEP_MSG);
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, THINK_MSG);
		if (philo->data->someone_died)
			break ;
		if (philo->data->number_of_philosophers % 2)
			usleep((philo->data->time_to_die - (get_current_time()
						- philo->last_meal_time)) * 0.9 * 1000);
	}
	return (NULL);
}
