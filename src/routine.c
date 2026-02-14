/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmustonen <martinmustonen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:02 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/14 22:57:48 by martinmusto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	precise_sleep(long duration_ms, t_vars *vars)
{
	long	start;

	start = get_time_in_ms();
	while (!simulation_stopped(vars) && get_time_in_ms() - start < duration_ms)
		usleep(200);
}

static void	think_delay(t_philo *philo)
{
	long	delay_ms;

	if (philo->vars->philos_size % 2 == 0)
		return ;
	delay_ms = (philo->vars->time_to_eat * 2) - philo->vars->time_to_sleep;
	if (delay_ms <= 0)
		return ;
	if (delay_ms > philo->vars->time_to_eat)
		delay_ms = philo->vars->time_to_eat;
	precise_sleep(delay_ms / 2, philo->vars);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	print_state(philo, "taken a fork");
	pthread_mutex_lock(second);
	print_state(philo, "taken a fork");
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	precise_sleep(philo->vars->time_to_eat, philo->vars);
	release_forks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "taken a fork");
		precise_sleep(philo->vars->time_to_die, philo->vars);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_sleep(philo->vars->time_to_eat / 2, philo->vars);
	while (!simulation_stopped(philo->vars))
	{
		print_state(philo, "is thinking");
		think_delay(philo);
		eat(philo);
		if (simulation_stopped(philo->vars))
			break ;
		print_state(philo, "is sleeping");
		precise_sleep(philo->vars->time_to_sleep, philo->vars);
	}
	return (NULL);
}
