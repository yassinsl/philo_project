/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:58 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/30 11:29:59 by ylahssin         ###   ########.fr       */
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

bool should_stop(t_philos *philo)
{
    bool stop;

    pthread_mutex_lock(philo->data->death_mutex);
    stop = philo->data->someone_died;
    pthread_mutex_unlock(philo->data->death_mutex);
    return (stop);
}

void ft_usleep(int duration, t_philos *philos)
{
    long start = get_current_time();
    while (!should_stop(philos))
    {
        if (get_current_time() - start >= duration)
            break;
        usleep(100);
    }
}

int take_forks(t_philos *philo)
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
        return (-1);
    }
    print_status(philo, TAKE_FORK);
    
    pthread_mutex_lock(&philo->data->forks[second_fork]);
    if (should_stop(philo))
    {
        pthread_mutex_unlock(&philo->data->forks[first_fork]);
        pthread_mutex_unlock(&philo->data->forks[second_fork]);
        return (-1);
    }
    print_status(philo, TAKE_FORK);
    return (0);
}

void philo_eat(t_philos *philo)
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

void one_philos(t_philos *philos)
{
    print_status(philos, TAKE_FORK);
    usleep(philos->data->time_to_die * 1000);
    print_status(philos, IS_DEAD_MSG);
    philos->data->someone_died = 1;
}

void *philo_routine(void *arg)
{
    t_philos *philo;

    philo = arg;
    if (philo->id % 2)
        usleep(1500);
    if (philo->data->number_of_philosophers == 1)
        return (one_philos(philo), NULL);
    
    while (1)
    {        
	pthread_mutex_lock(philo->data->death_mutex);
        if (philo->data->number_of_times_each_philosopher_must_eat != -1 && 
            philo->meals_eaten >= philo->data->number_of_times_each_philosopher_must_eat)
        {
           pthread_mutex_unlock(philo->data->death_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(philo->data->death_mutex);
        if (take_forks(philo) == -1)
            break;
        if (should_stop(philo))
        {
            pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
            pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
            break;
        } 
        philo_eat(philo);
        if (should_stop(philo))
            break;
        print_status(philo, SLEEP_MSG);
        ft_usleep(philo->data->time_to_sleep, philo);
        if (should_stop(philo))
            break;
        print_status(philo, THINK_MSG);
        if (philo->data->number_of_philosophers % 2)
        {
            pthread_mutex_lock(philo->data->death_mutex);
            long time_since_meal = get_current_time() - philo->last_meal_time;
            long time_left = philo->data->time_to_die - time_since_meal;
            pthread_mutex_unlock(philo->data->death_mutex);
            if (time_left > 0)
            {
                long think_time = (long)(time_left * 0.9);
                if (think_time > 0)
                    ft_usleep(think_time, philo);
            }
        }
    }
    return (NULL);
}
