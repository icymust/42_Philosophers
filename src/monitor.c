/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 23:22:18 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/17 13:15:20 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_death(t_vars *vars, int i)
{
	long	last_meal;
	long	current_time;

	pthread_mutex_lock(&vars->philos[i].meal_mutex);
	last_meal = vars->philos[i].last_meal;
	pthread_mutex_unlock(&vars->philos[i].meal_mutex);
	current_time = get_time_in_ms();
	if (current_time - last_meal > vars->time_to_die)
	{
		pthread_mutex_lock(&vars->state_mutex);
		vars->die = 1;
		pthread_mutex_unlock(&vars->state_mutex);
		pthread_mutex_lock(&vars->print_mutex);
		printf("%ld %d died\n", current_time - vars->start_time,
			vars->philos[i].id);
		pthread_mutex_unlock(&vars->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_fed(t_vars *vars)
{
	int	i;
	int	all_fed;

	i = 0;
	all_fed = 1;
	while (i < vars->philos_size)
	{
		pthread_mutex_lock(&vars->philos[i].meal_mutex);
		if (vars->philos[i].meals_eaten < vars->must_eat)
			all_fed = 0;
		pthread_mutex_unlock(&vars->philos[i].meal_mutex);
		i++;
	}
	if (all_fed)
	{
		pthread_mutex_lock(&vars->state_mutex);
		vars->die = 1;
		pthread_mutex_unlock(&vars->state_mutex);
	}
	return (all_fed);
}

void	*monitor_func(void *arg)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)arg;
	while (!simulation_stopped(vars))
	{
		i = 0;
		while (i < vars->philos_size)
		{
			if (check_death(vars, i))
				return (NULL);
			i++;
		}
		if (vars->must_eat != -1 && check_all_fed(vars))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
