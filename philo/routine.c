/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:19:20 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/02 17:09:51 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    pthread_mutex_lock(&philo->info->print_lock);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->info->print_lock);
    
    if(philo->id % 2 == 0)
        ft_usleep(philo->info->time_to_eat / 2, philo);
        
    while (1)
    {
        pthread_mutex_lock(&philo->info->dead_lock);
        if (philo->info->dead == 1 || philo->info->all_eaten == 1)
        {
            pthread_mutex_unlock(&philo->info->dead_lock);
            break;
        }
        pthread_mutex_unlock(&philo->info->dead_lock);
        
        pthread_mutex_lock(philo->right_fork);
        if (!print_state(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->right_fork);
            return (NULL);
        }
        
        if (philo->info->number_philo == 1)
        {
            pthread_mutex_unlock(philo->right_fork);
            ft_usleep(philo->info->time_to_die, philo);
            print_state(philo, "died");
            return (NULL);
        }
        
        pthread_mutex_lock(philo->left_fork);
        if (!print_state(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (NULL);
        }
        
        if (!print_state(philo, "is eating"))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (NULL);
        }
        
        pthread_mutex_lock(&philo->info->dead_lock);
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->info->dead_lock);
        
        pthread_mutex_lock(&philo->info->print_lock);
        philo->last_meal_time = get_current_time();
        pthread_mutex_unlock(&philo->info->print_lock);
        
        ft_usleep(philo->info->time_to_eat, philo);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        
        if (!print_state(philo, "is sleeping"))
            return (NULL);
        ft_usleep(philo->info->time_to_sleep, philo);

        if (!print_state(philo, "is thinking"))
            return (NULL);
    }
    return (NULL);
}
