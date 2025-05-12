#include "../includes/philos.h"

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

    if(*str == '-' || *str == '+')
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
void create_mutexes(t_data_philosophers *philos) {
    int i;
    
    i = -1;
    philos->forks = malloc(sizeof(pthread_mutex_t) * philos->number_of_philosophers);
    if (!philos->forks)
        ft_error_msg(ERROR_ALC);
    while (++i < philos->number_of_philosophers)
        if (pthread_mutex_init(&philos->forks[i], NULL))
            ft_error_msg(MUTEX_FAILED);
    if (pthread_mutex_init(&philos->print_mutex, NULL)||
        pthread_mutex_init(&philos->death_mutex, NULL))
        ft_error_msg(MUTEX_FAILED);
}

void create_philosophers(t_data_philosophers *data)
{
    int i;
    
    data->philos = malloc(sizeof(t_philos) * data->number_of_philosophers);
    if (!data->philos)
        ft_error_msg(ERROR_ALC);
    
    i = -1;
    while (++i < data->number_of_philosophers)
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

void get_data_from_args(t_data_philosophers *philos_data, char **av) 
{
    philos_data->number_of_philosophers = ft_atoi(av[1;]);
    philos_data->time_to_die = ft_atoi(av[2]);
    philos_data->time_to_eat = ft_atoi(av[3]);
    philos_data->time_to_sleep = ft_atoi(av[4]);
    
    if (av[5])
        philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    else
        philos_data->number_of_times_each_philosopher_must_eat = -1;
}
void think_random_time(int id)
{
    t_time time;
    int ms
    
    gettimofday(&time, NULL);
    ms = ((time.tv_usec + id * 1000) % 400 + 100) * 1000; //range the time bet 100 and 499 ms  
    usleep(ms);
}
void create_a_philos_routine(t_data_philosophers *philos)
{   
    t_create_philosophers *philos_data =  data->philos;

    while(1)
    {
        printf("Philosopher %d is thinking\n", id);
        think_random_time(philos_data->id);
        while (1) { 
            if (pthread_mutex_trylock(&forks[philos_data->left_fork]) == 0) {
                if (pthread_mutex_trylock(&forks[right_fork]) == 0) 
                {
                    printf("Philosopher %d is eating\n", id);
                    random_sleep(id);
                    pthread_mutex_unlock(&forks[right]);
                }
                pthread_mutex_unlock(&forks[left]);
            } 
            else 
                usleep(1000); 
        }
        
    }
}
int main(int ac, char *av[])
{
    t_data_philosophers philos_data;

    philos_data = (t_data_philosophers){0};
    //here i check the if the args are validet :)
    if(ac  != 5 || ac != 6)
        ft_error_msg(INVALID_NUMBER);
    get_data_from_args(&philos_data, av); 
    create_philosophers(&philos_data);
    create_a_philos_routine(&philos_data);
    return FALSE;
}
