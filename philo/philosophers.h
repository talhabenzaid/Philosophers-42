/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:59:32 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/04 09:23:58 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				must_eat;
	int				dead;
	int				all_eaten;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	int				meals_eaten;
	struct s_info	*info;
}	t_philo;

int		check_death(t_philo *philo);
void	check_meals(t_philo *philo);
int		ft_usleep(long period, t_philo *philo);
int		ft_check(t_philo *philo);
int		pars(char **str, int argc);
void	init(int num, char **str, t_info *info);
int		ft_atoi(char *str);
void	*philosopher_routine(void *arg);
long	get_current_time(void);
int		print_state(t_philo *philo, const char *state);
void	cleanup_resources(t_info *info, pthread_t *threads);

#endif
