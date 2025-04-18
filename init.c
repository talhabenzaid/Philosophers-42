/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:06:48 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/18 16:13:45 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_info(int num,char **str,t_info *info)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    info->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    info->number_philo = ft_atoi(str[1]);
    info->time_to_die = ft_atoi(str[2]);
    info->time_to_eat = ft_atoi(str[3]);
    info->time_to_sleep = ft_atoi(str[4]);
    info->must_eat = -1;
    if(num == 6)
        info->must_eat = ft_atoi(str[5]);
    info->dead = 0;
    int i = 0;
    info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
    if(!info->forks)
        return;
    if (!info->forks)
        return;
    while(i < info->number_philo)
    {
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }   
}

void print_state(t_philo *philo, const char *state)
{
    struct timeval tv;
    long time ;
    gettimeofday(&tv,NULL);
    time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philo->info->start_time;
    // pthread_mutex_lock(philo->info->print_lock);
    printf("%lu %d %s\n",time, philo->id, state);
    // pthread_mutex_unlock(philo->info->print_lock);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {

        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "taken a fork");
        print_state(philo, "is eating");
        usleep(philo->info->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        print_state(philo, "is sleeping");
        usleep(philo->info->time_to_sleep * 1000);

        print_state(philo, "is thinking");
        
    }

    return NULL;
}



void init(int num ,char **str)
{
    int i = 0;
    int j = 0;
    t_info *info = malloc(sizeof(t_info));
    if(!info)
        return;
    init_info(num,str,info);
    t_philo *philo = malloc(sizeof(t_philo) * info->number_philo);
    if(!philo)
        return;
    info->philos = philo;
    while(i < info->number_philo)
    {
        info->philos[i].id = i + 1;
        info->philos[i].info = info;
        info->philos[i].left_fork = &info->forks[i];
        info->philos[i].right_fork = &info->forks[(i + 1) % info->number_philo];
        i++;
    }
    pthread_t *threads = malloc(sizeof(pthread_t) * info->number_philo);
    if (!threads)
        return;

    while(j < info->number_philo)
    {
        pthread_create(&threads[j], NULL, philosopher_routine, &info->philos[j]);
        j++;
    }
    j = 0;
    while(j < info->number_philo)
    {
        pthread_join(threads[j], NULL);
        j++;
    }
    free(threads);
    
}