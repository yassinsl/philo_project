#ifndef PHILOS_H
#define PHILOS_H

#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include "../Libft/libft.h"

#define TRUE 1
#define FALSE 0
#define INVALID_NUMBER "Error: Invalid number of arguments\n\
        Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
        [number_of_times_each_philosopher_must_eat]\n"
#define INVALID_ARGS "Error: Invalid Arguments\n"

typedef struct s_data_philos t_data_philosophers;

typedef struct s_create_philos
{
    int id;
    int left_fork;
    int right_fork;
    long long last_meal_time;
    int meals_eaten;
    int is_dead;
    pthread_t thread;
    t_data_philosophers *data;
} t_philos;

typedef struct s_data_philos
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int idx;
    int someone_died;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *death_mutex;
    t_philos *philos;
} t_data_philosophers;

// Function prototypes
void ft_error_msg(char *msg);
int ft_atoi(char *str);
long long get_current_time(void);
long long get_timestamp(t_data_philosophers *data);
void create_mutexes(t_data_philosophers *philos);
void create_philosophers(t_data_philosophers *data);
void get_data_from_args(t_data_philosophers *philos_data, char **av);
void think_random_time(int id);
void *create_a_philos_routine(void *arg);
void *monitor_routine(void *arg);
void free_resources(t_data_philosophers *philos);
void create_threads(t_data_philosophers *philos);

#endif
