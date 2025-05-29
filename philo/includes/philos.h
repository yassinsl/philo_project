/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:15:12 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/29 18:43:28 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_ALC "Error: Allocation Failed\n"
# define MUTEX_FAILED "Error: Mutex initialization failed\n"
# define ONE_MSECOND 1000

# define THINK_MSG    "\033[1;31mis thinking\033[0m"     // Red
# define TAKE_FORK    "\033[1;32mhas taken a fork\033[0m" // Green
# define EAT_MSG      "\033[1;34mis eating\033[0m"       // Blue
# define SLEEP_MSG    "\033[1;33mis sleeping\033[0m"     // Yellow
# define IS_DEAD_MSG  "\033[1;31mis dead\033[0m"         // Red
# define TRUE 1
# define FALSE 0
#define INVALID_NUMBER \
	"\033[1;31mError: Invalid number of arguments\033[0m\n" \
	"	\033[1;34mUsage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep" \
	" [number_of_times_each_philosopher_must_eat]\033[0m\n"
# define INVALID_ARGS "Error: Invalid Arguments\n"

typedef struct s_data_philos	t_data_philosophers;

typedef struct s_create_philos
{
	int							id;
	int							left_fork;
	int							right_fork;
	long long					last_meal_time;
	int							meals_eaten;
	int							is_dead;
	pthread_t					thread;
	t_data_philosophers			*data;
}								t_philos;

typedef struct s_data_philos
{
	pthread_t					monitor;
	int							number_of_philosophers;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							number_of_times_each_philosopher_must_eat;
	int							idx;
	int							someone_died;
	long long					start_time;
	pthread_mutex_t				*forks;
	pthread_mutex_t				*print_mutex;
	pthread_mutex_t				*death_mutex;
	t_philos					*philos;
}								t_data_philosophers;

void							print_status(t_philos *philo, char *msg);
void							*philo_routine(void *arg);
void							ft_error_msg(char *msg);
int								ft_atoi(char *str);
long long						get_current_time(void);
long long						get_timestamp(t_data_philosophers *data);
int								create_mutexes(t_data_philosophers *philos);
void							create_philosophers(t_data_philosophers *data);
void							think_random_time(int id);
void							*create_a_philos_routine(void *arg);
void							*monitor_routine(void *arg);
void							free_resources(t_data_philosophers *philos);
int create_threads(t_data_philosophers *philos);
int								get_data_from_args(t_data_philosophers *data,
									char **av);
void ft_usleep(int duration, t_philos  *data);
bool should_stop(t_philos *philo);
#endif
