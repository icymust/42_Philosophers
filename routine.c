/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:02 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/06 16:45:57 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void take_forks(t_philo *philo){
    if(philo->id %2 ==0){
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "taken a fork");
    }
    else {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "taken a fork");
    }
}

void eat(t_philo *philo)
{
    take_forks(philo);

    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time_in_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);

    print_state(philo, "is eating");
    usleep(philo->vars->time_to_eat * 1000);

    release_forks(philo);
}

void *monitor(void *arg)
{
    t_vars  *vars = (t_vars *)arg;
    int     i;

    while (!vars->die)
    {
        i = 0;
        while (i < vars->philos_size)
        {
            if (get_time_in_ms() - vars->philos[i].last_meal > vars->time_to_die)
            {
                pthread_mutex_lock(&vars->state_mutex);
                vars->die = 1;
                pthread_mutex_unlock(&vars->state_mutex);

                pthread_mutex_lock(&vars->print_mutex);
                printf("%ld %d died\n",
                    get_time_in_ms() - vars->start_time,
                    vars->philos[i].id);
                pthread_mutex_unlock(&vars->print_mutex);

                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}


void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    monitor(*arg);
    while (!philo->vars->die)
    {
        pthread_mutex_lock(&philo->vars->print_mutex);
        if (!philo->vars->die)
            printf("%ld %d is thinking\n",
                get_time_in_ms() - philo->vars->start_time,
                philo->id);
        pthread_mutex_unlock(&philo->vars->print_mutex);

        usleep(1000);

        pthread_mutex_lock(&philo->vars->print_mutex);
        if (!philo->vars->die)
            printf("%ld %d is sleeping\n",
                get_time_in_ms() - philo->vars->start_time,
                philo->id);
        pthread_mutex_unlock(&philo->vars->print_mutex);

        usleep(philo->vars->time_to_sleep * 1000);
    }
    return (NULL);
}

