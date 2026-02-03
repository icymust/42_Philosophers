/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:02 by mmustone          #+#    #+#             */
/*   Updated: 2026/02/03 16:58:17 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    // просто тест
    pthread_mutex_lock(&philo->vars->print_mutex);
    printf("%ld %d is thinking\n",
        get_time_in_ms() - philo->vars->start_time,
        philo->id);
    pthread_mutex_unlock(&philo->vars->print_mutex);

    return (NULL);
}
