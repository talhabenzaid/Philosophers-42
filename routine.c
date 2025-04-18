/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:19:20 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/18 22:20:01 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_state(t_philo *philo, const char *state)
{
    long time ;
    time = get_current_time() - philo->info->start_time;
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
        print_state(philo, "has taken a fork");
        print_state(philo, "has taken a fork");
        
        print_state(philo, "is eating");
        usleep(philo->info->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        print_state(philo, "is sleeping");
        usleep(philo->info->time_to_sleep * 1000);

        print_state(philo, "is thinking");

        
        
    }

    return (NULL);
}