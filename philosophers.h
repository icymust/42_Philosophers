/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:56:32 by mmustone          #+#    #+#             */
/*   Updated: 2026/01/21 12:56:40 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // pthread
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free, atoi
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // usleep

typedef struct s_vars
{
    int phils;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat; // -1

    long start_time;

    int die; // 0/1
    int finish; // 0/1
    
    pthread_mutex_t print_mutex; // защита printf
    pthread_mutex_t state_mutex; // защита died / finished
    pthread_mutex_t *forks; // массив вилок
} t_vars;

typedef struct s_philo 
{
    int id;
    pthread_t thread;
    long last_meal;
    int meals_eaten;

    pthread_mutex_t meal_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;

    t_vars *vars;
} t_philo;

#endif