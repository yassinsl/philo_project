#ifndef PHILOS_H
#define PHILOS_H
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include "../Libft/libft.h"

#define TRUE 1
#define FALSE 0
#define INVALID_NUMBER "Error: Invalid number of arguments\n\
        Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
        [number_of_times_each_philosopher_must_eat]\n"
#define INVALID_ARGS "Error: Invalid Argements\n"
//this the struct to get a valid argement;
typedef struct s_data_philos
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
} t_data_philosophers;

#endif
