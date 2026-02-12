/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:35:27 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/13 00:35:28 by martinmust       ###   ########.fr       */
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
	vars->start_time = get_time_in_ms();
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

	pthread_create(monitor, NULL, monitor_func, vars);
	i = 0;
	while (i < vars->philos_size)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			vars->die = 1;
			break ;
		}
		i++;
		(*created)++;
	}
	return (0);
}

static void	wait_simulation(t_philo *philos, int created, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
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
	wait_simulation(philos, created, monitor_thread);
	cleanup(&vars, philos);
	return (0);
}
