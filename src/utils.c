/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:37:46 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/13 00:18:32 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_state(t_philo *philo, char *str)
{
	int	stopped;

	pthread_mutex_lock(&philo->vars->state_mutex);
	stopped = philo->vars->die;
	pthread_mutex_unlock(&philo->vars->state_mutex);
	if (!stopped)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%ld %d %s\n", get_time_in_ms() - philo->vars->start_time,
			philo->id, str);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	cleanup_resources(t_vars *vars, t_philo *philos)
{
	int	i;

	if (philos)
	{
		i = -1;
		while (++i < vars->philos_size)
			pthread_mutex_destroy(&philos[i].meal_mutex);
		free(philos);
	}
	if (vars->forks)
	{
		i = -1;
		while (++i < vars->philos_size)
			pthread_mutex_destroy(&vars->forks[i]);
		free(vars->forks);
	}
	if (vars->print_mutex_init)
		pthread_mutex_destroy(&vars->print_mutex);
	if (vars->state_mutex_init)
		pthread_mutex_destroy(&vars->state_mutex);
}

void	cleanup(t_vars *vars, t_philo *philos)
{
	cleanup_resources(vars, philos);
}
