/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:19:20 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/23 15:12:21 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int print_state(t_philo *philo, const char *state)
{
    long time;
    pthread_mutex_lock(&philo->info->print_lock);
     pthread_mutex_lock(&philo->info->dead_lock);
    if (philo->info->dead == 1)
    {
        pthread_mutex_unlock(&philo->info->dead_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->dead_lock);
    time = get_current_time() - philo->info->start_time;
    printf("%lu %d %s\n", time, philo->id, state);
    pthread_mutex_unlock(&philo->info->print_lock);
    return (1);
}

int ft_check(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->dead_lock);
    long last_meal = get_current_time() - philo->last_meal_time;
    
    if (last_meal >= philo->info->time_to_die)
    {
        printf("gg\n");
        pthread_mutex_unlock(&philo->info->dead_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->dead_lock);
    return (1);
}

int check_death(t_philo *philo)
{
    int i;
    int n;
    int nump;
    
    i = 0;
    nump = philo->info->number_philo;
    while(i)
    {
        usleep(500);
        pthread_mutex_lock(&philo->info->dead_lock);
        if(!ft_check(&philo[i]))
        {
            n = i;
            i = 0;
            while (i < nump)
            {
                philo[i].info->dead = 1;
                i++;
            }
            pthread_mutex_unlock(&philo->info->dead_lock);
            printf("%d died\n", n + 1);
            return (0);
        }
        pthread_mutex_unlock(&philo->info->dead_lock);
        i++;
        if (i == nump)
            i = 0;
    }
    return(1);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    philo->last_meal_time = get_current_time();
    if(philo->id % 2 == 0)
        usleep(500);
    while (1)
    {
        pthread_mutex_lock(&philo->info->dead_lock);
        if (philo->info->dead == 1)
        {
            pthread_mutex_unlock(&philo->info->dead_lock);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->info->dead_lock);

        pthread_mutex_lock(philo->left_fork);
        if (!print_state(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (NULL);
        }

        if (philo->info->number_philo == 1)
        {
            usleep(philo->info->time_to_die * 1000);
            print_state(philo, "died");
            return (NULL);
        }

        pthread_mutex_lock(philo->right_fork);
        if (!print_state(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return (NULL);
        }

        if (!print_state(philo, "is eating"))
            return (NULL);
        philo->last_meal_time = get_current_time();
        usleep(philo->info->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        if (!print_state(philo, "is sleeping"))
            return (NULL);
        usleep(philo->info->time_to_sleep * 1000);

        if (!print_state(philo, "is thinking"))
            return (NULL);
    }

    return (NULL);
}

