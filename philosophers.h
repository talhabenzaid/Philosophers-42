#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>


typedef struct s_time
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int start_time;

} t_time
;
typedef struct s_philo
{
    int id;
    pthread_t thread;
    int last_meal;
    int meals_eaten;

} t_philo;


typedef struct s_data
{
    int num_philos;
    int number_meal;
    int dead;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t meal_lock;
} t_data;

int pars(char **str,int argc);

#endif