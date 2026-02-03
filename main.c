/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:18:37 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/03 17:40:56 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;
	int created;

	vars.forks = NULL;
	philos = NULL;
	i = 0;
	created = 0;
	if (ac < 5 || ac > 6)
	{
		printf("./philo <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat]\n");
		return (1);
	}
	if (assign_vars(&vars, ac, av))
		return (1);
	vars.start_time = get_time_in_ms();
	if (init_philos(&vars, &philos))
	{
		cleanup(&vars, philos);
		return (1);
	}
	if (init_forks_and_mutex(&vars, philos))
	{
		cleanup(&vars, philos);
		return (1);
	}
	// потоки
	i = 0;
	while (i < vars.philos_size)
	{
		if (pthread_create(&philos[i].thread, NULL,
				routine, &philos[i]) != 0)
		{
			vars.die = 1;
			break;
		}
		i++;
		created++;
	}

	i = 0;
	while (i < created)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}

	cleanup(&vars, philos);
	return (0);
}
