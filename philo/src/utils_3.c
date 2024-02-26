/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:23:37 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 00:08:23 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
	{
		printf("Mutex destroy fail!\n");
		exit(0);
	}
}

int	dead_loop(t_philo *philo)
{
	if (philo->dead)
	{
		safe_mutex_lock(philo->dead_mod);
		printf("DEAD DEAD:%d\n", philo->id);
		return (safe_mutex_unlock(philo->dead_mod), 1);
	}
	return (0);
}

void	mutex_destry_all(t_monitor *monitor)
{
	long	i;

	i = monitor->philo->philo_nbr;
	while (i)
	{
		pthread_mutex_destroy(monitor->philo[i].fork_l);
		pthread_mutex_destroy(monitor->philo[i].eat_mod);
		i--;
	}
}
