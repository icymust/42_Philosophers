/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:56:32 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/13 00:23:33 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_vars
{
	int					philos_size;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;

	t_philo				*philos;

	long				start_time;

	int					die;
	int					finish;

	pthread_mutex_t		print_mutex;
	pthread_mutex_t		state_mutex;
	pthread_mutex_t		*forks;

	int					forks_init;
	int					print_mutex_init;
	int					state_mutex_init;
}						t_vars;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				last_meal;
	int					meals_eaten;

	pthread_mutex_t		meal_mutex;
	int					meal_mutex_init;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

	t_vars				*vars;
}						t_philo;

int						init_forks_and_mutex(t_vars *vars, t_philo *philos);
int						init_philos(t_vars *vars, t_philo **philos);
int						assign_vars(t_vars *vars, int ac, char **av);
long					get_time_in_ms(void);
void					print_state(t_philo *philo, char *str);
void					release_forks(t_philo *philo);
void					cleanup(t_vars *vars, t_philo *philos);
void					*routine(void *arg);
void					*monitor_func(void *arg);
int						simulation_stopped(t_vars *vars);

#endif