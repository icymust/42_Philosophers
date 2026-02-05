/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:02 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/05 17:52:04 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

        usleep(1000); // 1 ms, чтобы не крутиться вхолостую

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

