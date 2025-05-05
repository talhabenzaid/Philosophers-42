/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:06:48 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/05 16:52:15 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_info(int num, char **str, t_info *info)
{
	int	i;

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
	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	if (!info->forks)
		return ;
	while (i < info->number_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
}

void	init_philosophers(t_info *info,t_philo *philo)
{
	int		i;

	i = 0;
	info->philos = philo;
	while (i < info->number_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		if (i % 2 == 0)
		{
			info->philos[i].left_fork
				= &info->forks[(i + 1) % info->number_philo];
			info->philos[i].right_fork = &info->forks[i];
		}
		else
		{
			info->philos[i].left_fork = &info->forks[i];
			info->philos[i].right_fork
				= &info->forks[(i + 1) % info->number_philo];
		}
		info->philos[i].meals_eaten = 0;
		i++;
	}
}

void init_pthread(t_info *info,pthread_t	*threads)
{
	int			j;
	j = 0;

	while (j < info->number_philo)
	{
		if(pthread_create(&threads[j], NULL,philosopher_routine, &info->philos[j]) == -1)
		{
			cleanup_resources(info, NULL);
			return;
		}
		j++;
	}
	j = 0;
	if (info->philos->info->number_philo != 1)
		check_death(info->philos);
	while (j < info->number_philo)
	{
		if(pthread_join(threads[j], NULL) == -1)
		{
			cleanup_resources(info, NULL);
			return;
		}
		j++;
	}
}
