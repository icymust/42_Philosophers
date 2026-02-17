/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:02 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/17 14:59:17 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	smart_sleep(t_vars *vars, long ms)
{
	long	start;

	start = get_time_in_ms();
	while (!simulation_stopped(vars))
	{
		if (get_time_in_ms() - start >= ms)
			break ;
		usleep(200);
	}
}

int	simulation_stopped(t_vars *vars)
{
	int	stopped;

	pthread_mutex_lock(&vars->state_mutex);
	stopped = vars->die;
	pthread_mutex_unlock(&vars->state_mutex);
	return (stopped);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	smart_sleep(philo->vars, philo->vars->time_to_eat);
	release_forks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		smart_sleep(philo->vars, philo->vars->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(3000);
	while (!simulation_stopped(philo->vars))
	{
		print_state(philo, "is thinking");
		eat(philo);
		if (simulation_stopped(philo->vars))
			break ;
		print_state(philo, "is sleeping");
		smart_sleep(philo->vars, philo->vars->time_to_sleep);
		think_delay(philo);
	}
	return (NULL);
}
