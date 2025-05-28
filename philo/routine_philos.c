/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:58 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/28 15:19:03 by ylahssin         ###   ########.fr       */
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
int ft_usleep(long int time_in_ms)
{
    long int start_time;
    long int current_time;
    long int remaining;

    start_time = get_current_time();
    while (1)
    {
        current_time = get_current_time();
        remaining = time_in_ms - (current_time - start_time);

        if (remaining <= 0)
            break;

        // Use smaller sleep intervals for better precision
        if (remaining > 1)
            usleep(remaining * 1000 / 2);  // Sleep half the remaining time
        else
            usleep(100);  // Very short sleep for final precision
    }
    return (1);
}

bool should_stop(t_philos *philo)
{
    bool stop;

    pthread_mutex_lock(philo->data->death_mutex);
    stop = philo->data->someone_died;
    pthread_mutex_unlock(philo->data->death_mutex);
    return (stop);
}
void take_forks(t_philos *philo)
{
    int first_fork;
    int second_fork;

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
    if (should_stop(philo))
    {
        pthread_mutex_unlock(&philo->data->forks[first_fork]);
        return;
    }
    print_status(philo, TAKE_FORK);
    
    pthread_mutex_lock(&philo->data->forks[second_fork]);
    if (should_stop(philo))
    {
        pthread_mutex_unlock(&philo->data->forks[first_fork]);
        pthread_mutex_unlock(&philo->data->forks[second_fork]);
        return;
    }
    print_status(philo, TAKE_FORK);
}
void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->data->death_mutex);
	print_status(philo, EAT_MSG);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(philo->data->death_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	one_philos(t_philos *philos)
{
	print_status(philos, "has taken a fork");
	ft_usleep(philos->data->time_to_die);
	print_status(philos, "is dead");
	philos->data->someone_died = 1;
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (philo->id % 2)
		ft_usleep(1);
	if (philo->data->number_of_philosophers == 1)
		return (one_philos(philo), NULL);
	while (!should_stop(philo))
	{
		take_forks(philo);
		if(should_stop(philo))
			break;
		philo_eat(philo);
		if(should_stop(philo))
			break;
		print_status(philo, SLEEP_MSG);
		usleep(philo->data->time_to_sleep);
		if(should_stop(philo))
			break;
		print_status(philo, THINK_MSG);
		if(should_stop(philo))
			break;
		if (philo->data->number_of_philosophers % 2)
			ft_usleep(1);
	}
	return (NULL);
}
