/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:41 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 11:12:19 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * create_mutexes -I created a mutex for each fork, printed something,
	and changed the data.
 * @fork: Forks Mutex
 * @print_mutex: Print Mutex
 * @death_mutex : Death Mutex
 * Return: 0 if succeeded or -1
 */

int	create_mutexes(t_data_philosophers *philos)
{
	int	i;

	philos->forks = malloc(sizeof(pthread_mutex_t)
			* philos->number_of_philosophers);
	i = -1;
	if (!philos->forks)
		return (-1);
	while (++i < philos->number_of_philosophers)
		pthread_mutex_init(&philos->forks[i], NULL);
	philos->print_mutex = malloc(sizeof(pthread_mutex_t));
	philos->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philos->print_mutex || !philos->death_mutex)
		return (-1);
	pthread_mutex_init(philos->print_mutex, NULL);
	pthread_mutex_init(philos->death_mutex, NULL);
	return (0);
}
