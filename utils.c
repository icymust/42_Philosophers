/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:37:46 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/03 16:50:14 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	cleanup(t_vars *vars, t_philo *philos)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < vars->philos_size)
		{
			pthread_mutex_destroy(&philos[i].meal_mutex);
			i++;
		}
		free(philos);
	}
	if (vars->forks)
	{
		i = 0;
		while (i < vars->philos_size)
		{
			pthread_mutex_destroy(&vars->forks[i]);
			i++;
		}
		free(vars->forks);
	}
	if (vars->print_mutex_init)
    {
        pthread_mutex_destroy(&vars->print_mutex);
        vars->print_mutex_init = 0;
    }

    if (vars->state_mutex_init)
    {
        pthread_mutex_destroy(&vars->state_mutex);
        vars->state_mutex_init = 0;
    }
}
