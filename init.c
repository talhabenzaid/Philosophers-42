/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:06:48 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/16 17:39:26 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_time(int num,char **str,t_info *info)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    info->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    info->number_philo = ft_atoi(str[1]);
    info->time_to_die = ft_atoi(str[2]);
    info->time_to_eat = ft_atoi(str[3]);
    info->time_to_sleep = ft_atoi(str[4]);
    info->must_eat = -1;
    if(num == 6)
        info->must_eat = ft_atoi(str[5]);
}
void init(int num ,char **str,t_info *info)
{
    set_time(num,str,info);
}