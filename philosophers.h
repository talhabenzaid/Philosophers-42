/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:59:32 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/22 16:15:07 by tbenzaid         ###   ########.fr       */
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
    long    last_meal_time;
    struct s_info   *info;
} t_philo;


int pars(char **str,int argc);
void init(int num ,char **str,t_info *info);
int ft_atoi(char *str);
void print_state(t_philo *philo, const char *state);
void *philosopher_routine(void *arg);
long get_current_time();
void print_state(t_philo *philo, const char *state);

#endif