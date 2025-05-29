/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:37:55 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/29 13:09:53 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * monitor_routine -continuously checks
 * 			if any philosopher has died or if all have finished eating.
 * all_ate_enough -checks if a philosopher has eaten the required
 * 			number of meals to be considered full.
 * Return(monitor) -NULL if succeeded
 * Return(all_ate_nough) -Return TRUE if succeed FALSE
 */

bool	all_ate_enough(t_data_philosophers *data)
{
	int		i;
	bool	all_done;
	int		num;

	num = data->number_of_times_each_philosopher_must_eat;
	if (data->number_of_times_each_philosopher_must_eat == -1)
		return (FALSE);
	all_done = TRUE;
	i = -1;
	pthread_mutex_lock(data->death_mutex);
	while (++i < data->number_of_philosophers)
	{
		if (data->philos[i].meals_eaten < num)
		{
			all_done = FALSE;
			break ;
		}
	}
	pthread_mutex_unlock(data->death_mutex);
	return (all_done);
}

int check_deaths(t_data_philosophers *data)
{
    int i;
    long long time_since_last_meal;

    i = -1;
    
    while (++i < data->number_of_philosophers)
    {
        pthread_mutex_lock(data->death_mutex);
        time_since_last_meal = get_current_time() - data->philos[i].last_meal_time;
        if (time_since_last_meal > data->time_to_die)
        {
            data->someone_died = 1;
            pthread_mutex_lock(data->print_mutex);
            printf("%lld %d is dead\n", get_timestamp(data), data->philos[i].id);
            pthread_mutex_unlock(data->print_mutex);            
            pthread_mutex_unlock(data->death_mutex);
            return (1);
        }
        pthread_mutex_unlock(data->death_mutex);
    }
    return (0);
}
void	*monitor_routine(void *arg)
{
	t_data_philosophers	*data;

	data = (t_data_philosophers *)arg;
	while (1)
	{
		pthread_mutex_lock(data->death_mutex);
		if (data->someone_died)
        	{
           	 pthread_mutex_unlock(data->death_mutex);
            	break;
        	}
        	pthread_mutex_unlock(data->death_mutex);
		if (check_deaths(data))
			return (NULL);
		if (all_ate_enough(data))
		{
			pthread_mutex_lock(data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(data->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
