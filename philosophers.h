#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_info
{
    int number_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long start_time;
    int must_eat;
    // int dead;
    // pthread_mutex_t *forks;
    // pthread_mutex_t print_lock;
    // pthread_mutex_t meal_lock;

} t_info
;
typedef struct s_philo
{
    int id;
    pthread_t thread;
    int last_meal;
    int meals_eaten;

} t_philo;


int pars(char **str,int argc);
void init(int num,char **str,t_info *info);
int ft_atoi(char *str);

#endif