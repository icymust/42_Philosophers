/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:18:37 by mmustone          #+#    #+#             */
/*   Updated: 2026/01/21 12:59:25 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_av(char *av){
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		return(-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return(-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		if (result * minus > INT_MAX)
			return (-1);
		if (result * minus < INT_MIN)
			return (0);
		str++;
	}
	return ((int)(result * minus));
}

int main(int ac, char **av){
    t_philo *philo;
    int i = 1;
    int num = 0;
    memset(&philo, 0, sizeof(t_vars));
    if(ac < 5 || ac > 6){
        printf("./philo <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep>\n");
        return(0);
    }
    while(i < 6){
        num = check_av(av[i]);
        if(num > 0)
        {
            if(i == 1)
                philo.vars.time_to_die = num;
            else if(i == 2)
                philo.vars.time_to_die = num;
            else if(i == 3) 
                philo.vars.time_to_eat = num;
            else if(i == 4)
                philo.vars.time_to_sleep = num;
            i++;
        }
        else
            return(0);
        
    }
    return(0);
}
