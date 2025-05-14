/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:19:20 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/14 08:48:57 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(long period, t_philo *philo)
{
	long	start;
	int		dead;

	start = get_current_time();
	while (get_current_time() - start < period)
	{
		pthread_mutex_lock(&philo->info->dead_lock);
		dead = philo->info->dead;
		pthread_mutex_unlock(&philo->info->dead_lock);
		if (dead)
			break ;
		usleep(100);
	}
	return (0);
}

void	*one_philo(t_philo *philo)
{
	if (philo->info->number_philo == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		ft_usleep(philo->info->time_to_die, philo);
		print_state(philo, "died");
		return (NULL);
	}
	return ((void *)1);
}

int	eat_phase(t_philo *philo)
{
	if (!print_state(philo, "is eating"))
		return (0);
	pthread_mutex_lock(&philo->info->print_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->info->print_lock);
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meal_lock);
	return (1);
}

void	*philosopher_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_state(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (!one_philo(philo))
		return (NULL);
	pthread_mutex_lock(philo->right_fork);
	if (!print_state(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), NULL);
	if (!eat_phase(philo))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), NULL);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (!print_state(philo, "is sleeping"))
		return (NULL);
	ft_usleep(philo->info->time_to_sleep, philo);
	if (!print_state(philo, "is thinking"))
		return (NULL);
	if (philo->id % 2 == 1)
		ft_usleep(2, philo);
	return ((void *)1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->info->dead_lock);
		if (philo->info->dead == 1 || philo->info->all_eaten == 1)
		{
			pthread_mutex_unlock(&philo->info->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->dead_lock);
		if (philosopher_actions(philo) == NULL)
			return (NULL);
	}
	return (NULL);
}
