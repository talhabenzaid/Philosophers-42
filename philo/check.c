/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:35:28 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/04 16:51:45 by tbenzaid         ###   ########.fr       */
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

int	print_state(t_philo *philo, const char *state)
{
	long	time;

	pthread_mutex_lock(&philo->info->print_lock);
	pthread_mutex_lock(&philo->info->dead_lock);
	if (philo->info->dead == 1 || philo->info->all_eaten == 1)
	{
		pthread_mutex_unlock(&philo->info->dead_lock);
		pthread_mutex_unlock(&philo->info->print_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->dead_lock);
	time = get_current_time() - philo->info->start_time;
	printf("%lu %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->info->print_lock);
	return (1);
}

int	ft_check(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->info->print_lock);
	last_meal = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->info->print_lock);
	if (last_meal >= philo->info->time_to_die)
	{
		pthread_mutex_lock(&philo->info->dead_lock);
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->dead_lock);
		return (0);
	}
	return (1);
}

void	check_meals(t_philo *philo)
{
	int	i;
	int	all_eaten;

	if (philo->info->must_eat == -1)
		return ;
	i = 0;
	all_eaten = 1;
	pthread_mutex_lock(&philo->info->dead_lock);
	while (i < philo->info->number_philo)
	{
		if (philo[i].meals_eaten < philo->info->must_eat)
		{
			all_eaten = 0;
			break ;
		}
		i++;
	}
	if (all_eaten)
		philo->info->all_eaten = 1;
	pthread_mutex_unlock(&philo->info->dead_lock);
}

int	check_death(t_philo *philo)
{
	int	i;

	while (1)
	{
		ft_usleep(500, philo);
		i = 0;
		while (i < philo->info->number_philo)
		{
			if (!ft_check(&philo[i]))
			{
				pthread_mutex_lock(&philo->info->print_lock);
				printf("%lu %d died\n",
					get_current_time() - philo->info->start_time,
					philo[i].id);
				pthread_mutex_unlock(&philo->info->print_lock);
				return (0);
			}
			i++;
		}
		check_meals(philo);
		pthread_mutex_lock(&philo->info->dead_lock);
		if (philo->info->all_eaten == 1)
		{
			pthread_mutex_unlock(&philo->info->dead_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->info->dead_lock);
	}
	return (1);
}
