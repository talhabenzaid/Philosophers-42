/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:33 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/13 20:46:24 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_resources(t_info *info, pthread_t *threads)
{
	int	i;

	if (threads)
		free(threads);
	if (info->forks)
	{
		i = 0;
		while (i < info->number_philo)
		{
			pthread_mutex_destroy(&info->forks[i]);
			i++;
		}
		free(info->forks);
	}
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->print_lock);
	pthread_mutex_destroy(&info->meal_lock);
	if (info->philos)
		free(info->philos);
	free(info);
}

int	init_fork_mutexes(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	if (!info->forks)
		return (0);
	i = 0;
	while (i < info->number_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&info->forks[i]);
			free(info->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_info *info)
{
	int	dead_lock_init;
	int	print_lock_init;
	int	meal_lock_init;
	int	i;

	if (!init_fork_mutexes(info))
		return (0);
	dead_lock_init = pthread_mutex_init(&info->dead_lock, NULL);
	print_lock_init = pthread_mutex_init(&info->print_lock, NULL);
	meal_lock_init = pthread_mutex_init(&info->meal_lock, NULL);
	if (dead_lock_init != 0 || print_lock_init != 0 || meal_lock_init != 0)
	{
		i = info->number_philo;
		while (--i >= 0)
			pthread_mutex_destroy(&info->forks[i]);
		free(info->forks);
		if (dead_lock_init == 0)
			pthread_mutex_destroy(&info->dead_lock);
		if (print_lock_init == 0)
			pthread_mutex_destroy(&info->print_lock);
		if (meal_lock_init == 0)
			pthread_mutex_destroy(&info->meal_lock);
		return (0);
	}
	return (1);
}

void	init(t_info *info)
{
	int			j;
	pthread_t	*threads;

	j = 0;
	threads = malloc(sizeof(pthread_t) * info->number_philo);
	if (!threads)
	{
		cleanup_resources(info, NULL);
		return ;
	}
	while (j < info->number_philo)
	{
		if (pthread_create(&threads[j], NULL,
				philosopher_routine, &info->philos[j]) != 0)
			cleanup_resources(info, threads);
		j++;
	}
	j = 0;
	(usleep(100), check_death(info->philos));
	while (j < info->number_philo)
	{
		pthread_join(threads[j], NULL);
		j++;
	}
	cleanup_resources(info, threads);
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	if (!pars(argv, argc))
		return (0);
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	(init_info(argc, argv, info), init_philosophers(info));
	info->start_time = get_current_time();
	init(info);
	return (0);
}
