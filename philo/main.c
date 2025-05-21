#include "../includes/philos.h"
#include <string.h>
#define ERROR_ALC "Error: Allocation Failed\n"
#define MUTEX_FAILED "Error: Mutex initialization failed\n"
#define ONE_MSECOND 1000
#define THINK_MSG "is thinking"
#define TAKE_FORK "has taken a fork"
#define EAT_MSG "is eating"
#define SLEEP_MSG "is sleeping"

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

void create_mutexes(t_data_philosophers *philos)
{
    int i;

    philos->forks = malloc(sizeof(pthread_mutex_t) * philos->number_of_philosophers);
    i = -1;
    if (!philos->forks)
        ft_error_msg(ERROR_ALC);
    while(++i < philos->number_of_philosophers)
        pthread_mutex_init(&philos->forks[i], NULL);
    
    philos->print_mutex = malloc(sizeof(pthread_mutex_t));
    philos->death_mutex = malloc(sizeof(pthread_mutex_t));
    if (!philos->print_mutex || !philos->death_mutex)
        ft_error_msg(ERROR_ALC);
    
    pthread_mutex_init(philos->print_mutex, NULL);
    pthread_mutex_init(philos->death_mutex, NULL);
}

long long get_current_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long get_timestamp(t_data_philosophers *data)
{
    return (get_current_time() - data->start_time);
}

void create_philosophers(t_data_philosophers *data)
{
    int i = -1;

    data->philos = malloc(sizeof(t_philos) * data->number_of_philosophers);

    while(++i < data->number_of_philosophers)
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

void print_status(t_philos *philo, char *msg)
{
    pthread_mutex_lock(philo->data->print_mutex);
    if (!philo->data->someone_died)
        printf("%lld %d %s\n", get_timestamp(philo->data), philo->id, msg);
    pthread_mutex_unlock(philo->data->print_mutex);
}

void take_forks(t_philos *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        print_status(philo, TAKE_FORK);
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        print_status(philo, TAKE_FORK);
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        print_status(philo, TAKE_FORK);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        print_status(philo, TAKE_FORK);
    }
}

void philo_eat(t_philos *philo)
{
    pthread_mutex_lock(philo->data->death_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(philo->data->death_mutex);
    print_status(philo, EAT_MSG);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_lock(philo->data->death_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->data->death_mutex);    
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void *philo_routine(void *arg)
{
    t_philos *philo;

    philo = (t_philos *)arg;
    if (philo->id % 2 != 0)
        usleep(ONE_MSECOND);    
    while (!philo->data->someone_died)
    {
        print_status(philo, THINK_MSG);
        take_forks(philo);
        philo_eat(philo);
        print_status(philo, SLEEP_MSG);
        usleep(philo->data->time_to_sleep * 1000);
    }
    return (NULL);
}

bool all_ate_enough(t_data_philosophers *data)
{
    int i;
    bool all_done;

    if (data->number_of_times_each_philosopher_must_eat == -1)
        return (FALSE);    
    all_done = TRUE;
    i = -1;
    while (++i < data->number_of_philosophers)
    {
        pthread_mutex_lock(data->death_mutex);
        if (data->philos[i].meals_eaten < data->number_of_times_each_philosopher_must_eat)
        {
            all_done = FALSE;
            pthread_mutex_unlock(data->death_mutex);
            break;
        }
        pthread_mutex_unlock(data->death_mutex);
    }
    return (all_done);
}

void *monitor_routine(void *arg)
{
    t_data_philosophers *data;
    int i;

    data = (t_data_philosophers *)arg;
    while (!data->someone_died)
    {
        i = -1;
        while (++i < data->number_of_philosophers)
        {
            pthread_mutex_lock(data->death_mutex);
            if (get_current_time() - data->philos[i].last_meal_time > data->time_to_die)
            {
                pthread_mutex_lock(data->print_mutex);
                printf("%lld %d is dead\n", get_timestamp(data), data->philos[i].id);
                data->someone_died = 1;
                pthread_mutex_unlock(data->print_mutex);
                pthread_mutex_unlock(data->death_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(data->death_mutex);
        }        
        if (all_ate_enough(data))
        {
            pthread_mutex_lock(data->death_mutex);
            data->someone_died = 1;
            pthread_mutex_unlock(data->death_mutex);
            return (NULL);
        }
        usleep(ONE_MSECOND);
    }
    return (NULL);
}

void free_resources(t_data_philosophers *philos)
{
    int i;
    
    if (philos)
    {
        i = -1;
        while (++i < philos->number_of_philosophers)
            pthread_mutex_destroy(&philos->forks[i]);
        pthread_mutex_destroy(philos->print_mutex);
        pthread_mutex_destroy(philos->death_mutex);        
        free(philos->forks);
        free(philos->print_mutex);
        free(philos->death_mutex);
        free(philos->philos);
    }
}

void create_threads(t_data_philosophers *data)
{
    int i;
    
    data->start_time = get_current_time();
    data->someone_died = 0;
    i = -1;
    while (++i < data->number_of_philosophers)
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]); 
    pthread_create(&data->monitor, NULL, monitor_routine, data);
    pthread_join(data->monitor, NULL);
    i = -1;
    while (++i < data->number_of_philosophers)
        pthread_join(data->philos[i].thread, NULL);
    free_resources(data);
}

int main(int ac, char *av[])
{
    t_data_philosophers philos_data;

    memset(&philos_data, 0, sizeof(t_data_philosophers));    
    if (ac != 5 && ac != 6)
        ft_error_msg(INVALID_NUMBER);
    get_data_from_args(&philos_data, av);
    create_mutexes(&philos_data);
    create_philosophers(&philos_data);
    create_threads(&philos_data);
    return 0;
}