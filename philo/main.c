#include "../includes/philos.h"
#include <sys/time.h>   // for gettimeofday
#include <limits.h>     // for INT_MAX, INT_MIN
#include <unistd.h>     // for write
#include <stdlib.h>     // for malloc, exit
#include <pthread.h>    // for pthread functions

#define ERROR_ALC "Error: Allocation Failed\n"
#define MUTEX_FAILED "Error: Mutex initialization failed\n"

typedef struct timeval t_time;

void ft_error_msg(char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(1);
}

int ft_atoi(char *str)
{
    long long num = 0;
    int sign = 1;

    if (*str == '-' || *str == '+') 
    {
        if (*str == '-')
            sign = -1;
        str++;
    }

    while (*str && (*str >= '0' && *str <= '9')) 
    {
        if ((sign == 1 && num > INT_MAX) || (sign == -1 && num > -(long long)INT_MIN))
            ft_error_msg(INVALID_ARGS);
        num = num * 10 + (*str++ - '0');
    }
    if (*str || num * sign <= 0)
        ft_error_msg(INVALID_ARGS);
    return (int)(sign * num);
}

void get_data_from_args(t_data_philosophers *philos_data, char **av)
{
    philos_data->number_of_philosophers = ft_atoi(av[1]);
    philos_data->time_to_die = ft_atoi(av[2]);
    philos_data->time_to_eat = ft_atoi(av[3]);
    philos_data->time_to_sleep = ft_atoi(av[4]);

    if (av[5])
        philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    else
        philos_data->number_of_times_each_philosopher_must_eat = -1;
}

void create_a_mutex(t_data_philosophers *philos)
{
    int i;

    philos->forks = malloc(sizeof(pthread_mutex_t) * philos->number_of_philosophers);
    if (!philos->forks)
        ft_error_msg(MUTEX_FAILED);

    for (i = 0; i < philos->number_of_philosophers; i++)
        pthread_mutex_init(&philos->forks[i], NULL);
    philos->print_mutex = malloc(sizeof(pthread_mutex_t));
    philos->death_mutex = malloc(sizeof(pthread_mutex_t));
    if (!philos->print_mutex || !philos->death_mutex)
        ft_error_msg(MUTEX_FAILED);
    pthread_mutex_init(philos->print_mutex, NULL);
    pthread_mutex_init(philos->death_mutex, NULL);
}

long long get_current_time(void)
{
    t_time time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void create_philosophers(t_data_philosophers *data)
{
    int i;

    data->philos = malloc(sizeof(t_philos) * data->number_of_philosophers);
    if (!data->philos)
        ft_error_msg(ERROR_ALC);

    for (i = 0; i < data->number_of_philosophers; i++)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->number_of_philosophers;
        data->philos[i].last_meal_time = get_current_time();
        data->philos[i].meals_eaten = 0;
        data->philos[i].is_dead = 0;
        data->philos[i].data = data;
    }
}

int main(int ac, char *av[])
{
    t_data_philosophers philos_data;

    philos_data = (t_data_philosophers){0};
    if (ac != 5 && ac != 6)
            ft_error_msg(INVALID_NUMBER);
    get_data_from_args(&philos_data, av);
    create_a_mutex(&philos_data);
    create_philosophers(&philos_data);
    return 0;
}
