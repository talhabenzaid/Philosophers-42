/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:06:48 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/17 14:21:03 by tbenzaid         ###   ########.fr       */
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
    if (!info->forks)
        return;
    while(i < info->number_philo)
    {
        pthread_mutex_init(info->fork[i], NULL);
        i++;
    }   
}


void init(int num ,char **str)
{
    int i = 0;
    t_info *info = malloc(sizeof(t_info));
    if(!info)
        return;
    init_info(num,str,info);
    t_philo *philo = malloc(sizeof(t_philo * info->number_philo));
    if(!philo)
        return;
    while(i < info->number_philo)
    {
        info->philos[i]->id = i;
        info->philos[i]->info = info;
        info->philos[i]->left_fork = &info->forks[i];
        info->philos[i]->right_fork = &info->forks[(i + 1) % info->number_philo];
        i++;
    }
    
}