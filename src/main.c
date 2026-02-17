/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:35:27 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/17 12:48:14 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_simulation(t_vars *vars, t_philo **philos, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("./philo <num_of_philo> <time_to_die> <time_to_eat> ");
		printf("<time_to_sleep> [must_eat]\n");
		return (1);
	}
	if (assign_vars(vars, ac, av))
		return (1);
	if (init_philos(vars, philos))
		return (1);
	if (init_forks_and_mutex(vars, *philos))
		return (1);
	return (0);
}

static int	start_threads(t_vars *vars, t_philo *philos, pthread_t *monitor,
		int *created)
{
	int	i;

	init_time(vars, philos);
	i = 0;
	while (i < vars->philos_size)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			pthread_mutex_lock(&vars->state_mutex);
			vars->die = 1;
			pthread_mutex_unlock(&vars->state_mutex);
			break ;
		}
		i++;
		(*created)++;
	}
	if (pthread_create(monitor, NULL, monitor_func, vars) != 0)
	{
		pthread_mutex_lock(&vars->state_mutex);
		vars->die = 1;
		pthread_mutex_unlock(&vars->state_mutex);
		return (1);
	}
	vars->monitor_init = 1;
	return (0);
}

static void	wait_simulation(t_philo *philos, int created, pthread_t monitor,
		int monitor_init)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	if (monitor_init)
		pthread_join(monitor, NULL);
}

int	main(int ac, char **av)
{
	t_vars		vars;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			created;

	vars.forks = NULL;
	philos = NULL;
	created = 0;
	if (init_simulation(&vars, &philos, ac, av))
	{
		cleanup(&vars, philos);
		return (1);
	}
	if (start_threads(&vars, philos, &monitor_thread, &created))
	{
		cleanup(&vars, philos);
		return (1);
	}
	wait_simulation(philos, created, monitor_thread, vars.monitor_init);
	cleanup(&vars, philos);
	return (0);
}
