/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:33 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/04 09:23:47 by tbenzaid         ###   ########.fr       */
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
