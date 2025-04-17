/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:59:32 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/17 19:05:10 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo t_philo; 

typedef struct s_info
{
    int number_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long start_time;
    int must_eat;
    int dead;
    pthread_mutex_t *forks;
    t_philo *philos;
} t_info
;

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_info   *info;
} t_philo;


int pars(char **str,int argc);
void init(int num,char **str);
int ft_atoi(char *str);

#endif