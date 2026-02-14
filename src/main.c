/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmustonen <martinmustonen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:35:27 by martinmust        #+#    #+#             */
/*   Updated: 2026/02/14 23:14:53 by martinmusto      ###   ########.fr       */
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

static void	join_created_threads(t_philo *philos, int created)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	start_timer(t_vars *vars, t_philo *philos)
{
	int	i;

	i = 0;
	vars->start_time = get_time_in_ms();
	while (i < vars->philos_size)
	{
		philos[i].last_meal = vars->start_time;
		i++;
	}
}

static int	start_threads(t_vars *vars, t_philo *philos, pthread_t *monitor,
		int *created)
{
	int	i;

	i = 0;
	start_timer(vars, philos);
	while (i < vars->philos_size)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			vars->die = 1;
			join_created_threads(philos, *created);
			return (1);
		}
		i++;
		(*created)++;
	}
	if (pthread_create(monitor, NULL, monitor_func, vars) != 0)
	{
		vars->die = 1;
		join_created_threads(philos, *created);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_vars		vars;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			created;

	memset(&vars, 0, sizeof(t_vars));
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
	join_created_threads(philos, created);
	pthread_join(monitor_thread, NULL);
	cleanup(&vars, philos);
	return (0);
}
