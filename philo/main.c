#include "../includes/philos.h"


void ft_error_msg(char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(1);
}

int ft_atoi(char *str)
{
    long long num = 0;
    int sign = 1;

    if(*str == '-' || *str)
    {
        if(*str == '-')
            sign = 1;
        str++;
    }
    while(*str && (*str >= '0' && *str <= '9'))
    {
        if((sign == 1 && num > INT_MAX )|| (sign ==-1 && num > -(long long)INT_MIN))
            ft_error_msg(INVALID_ARGS);
        num = num * 10 + (*str++ - '0');
    }
    if(*str || num  * sign <= 0)
        ft_error_msg(INVALID_ARGS);
    return((int)(sign * num));
}
void get_data_from_args(t_data_philosophers *philos_data, char **av)
{
    philos_data->number_of_philosophers = ft_atoi(av[1]);
    philos_data->time_to_die = ft_atoi(av[2]);
    philos_data->time_to_eat = ft_atoi(av[3]);
    philos_data->time_to_sleep = ft_atoi(av[4]);
} 

int main(int ac, char *av[])
{
    t_data_philosophers philos_data;

    philos_data = (t_data_philosophers){0};
    //here i check the if the args are validet :)
    if(ac < 5 || ac >= 6)
        ft_error_msg(INVALID_NUMBER);
    get_data_from_args(&philos_data, av);
    return FALSE;
}