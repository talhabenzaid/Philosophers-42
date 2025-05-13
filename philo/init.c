/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:06:48 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/13 20:37:10 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_info(int num, char **str, t_info *info)
{
	info->start_time = get_current_time();
	info->number_philo = ft_atoi(str[1]);
	info->time_to_die = ft_atoi(str[2]);
	info->time_to_eat = ft_atoi(str[3]);
	info->time_to_sleep = ft_atoi(str[4]);
	info->must_eat = -1;
	info->all_eaten = 0;
	if (num == 6)
		info->must_eat = ft_atoi(str[5]);
	info->dead = 0;
	if (!init_mutexes(info))
	{
		free(info);
		return ;
	}
}

void	allocate_philosophers(t_info *info)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * info->number_philo);
	if (!philo)
		return ;
	info->philos = philo;
}

void	assign_forks(t_philo *philo, t_info *info, int i)
{
	if (i % 2 == 0)
	{
		philo->left_fork = &info->forks[(i + 1) % info->number_philo];
		philo->right_fork = &info->forks[i];
	}
	else
	{
		philo->left_fork = &info->forks[i];
		philo->right_fork = &info->forks[(i + 1) % info->number_philo];
	}
}

void	init_philosophers(t_info *info)
{
	int	i;

	i = 0;
	allocate_philosophers(info);
	if (!info->philos)
		return ;
	while (i < info->number_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].last_meal_time = info->start_time;
		info->philos[i].meals_eaten = 0;
		assign_forks(&info->philos[i], info, i);
		i++;
	}
}
