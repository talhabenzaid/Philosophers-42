/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:33 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/05 16:51:16 by tbenzaid         ###   ########.fr       */
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
	if (info->philos)
		free(info->philos);
	free(info);
}

void	init(int num, char **str, t_info *info)
{
	
	pthread_t	*threads;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * info->number_philo);
	if (!philo)
		return ;
	init_info(num, str, info);
	init_philosophers(info, philo);
	threads = malloc(sizeof(pthread_t) * info->number_philo);
	if (!threads)
	{
		cleanup_resources(info, NULL);
		return ;
	}
	init_pthread(info,threads);
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
	init(argc, argv, info);
	return (0);
}
