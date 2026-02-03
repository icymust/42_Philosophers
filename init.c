/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:37:50 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/03 17:39:25 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_av(char *av)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!av || av[0] == '\0')
		return (-1);
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (-1);
		result = result * 10 + (av[i] - '0');
		i++;
	}
	if (result <= 0)
		return (-1);
	return (result);
}

int	init_philos(t_vars *vars, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * vars->philos_size);
	if (!*philos)
		return (1);
	memset(*philos, 0, sizeof(t_philo) * vars->philos_size);
	i = 0;
	while (i < vars->philos_size)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].vars = vars;
		(*philos)[i].last_meal = vars->start_time;
		if (pthread_mutex_init(&(*philos)[i].meal_mutex, NULL) != 0)
			return (1);
		(*philos)[i].meal_mutex_init = 1;
		i++;
	}
	return (0);
}

int	init_forks_and_mutex(t_vars *vars, t_philo *philos)
{
	int	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_size);
	if (!vars->forks)
		return (1);
	i = 0;
	while (i < vars->philos_size)
	{
		if (pthread_mutex_init(&vars->forks[i], NULL) != 0)
			return (1);
		vars->forks_init++;
		philos[i].left_fork = &vars->forks[i];
		philos[i].right_fork = &vars->forks[(i + 1) % vars->philos_size];
		i++;
	}
	if (pthread_mutex_init(&vars->print_mutex, NULL) != 0)
		return (1);
	vars->print_mutex_init = 1;
	if (pthread_mutex_init(&vars->state_mutex, NULL) != 0)
		return (1);
	vars->state_mutex_init = 1;
	return (0);
}

int	assign_vars(t_vars *vars, int ac, char **av)
{
	memset(vars, 0, sizeof(t_vars));
	vars->philos_size = check_av(av[1]);
	vars->time_to_die = check_av(av[2]);
	vars->time_to_eat = check_av(av[3]);
	vars->time_to_sleep = check_av(av[4]);
	vars->must_eat = -1;
	if (vars->philos_size <= 0 || vars->time_to_die <= 0
		|| vars->time_to_eat <= 0 || vars->time_to_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		vars->must_eat = check_av(av[5]);
		if (vars->must_eat <= 0)
			return (1);
	}
	return (0);
}
