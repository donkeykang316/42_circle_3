/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:23:37 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 19:35:07 by kaan             ###   ########.fr       */
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
	if (*(philo->monitor->dead))
	{
		safe_mutex_lock(philo->dead_mod);
		printf("%ld %d died\n", time_stamp(philo->start), philo->id);
		return (safe_mutex_unlock(philo->dead_mod), 1);
	}
	if (*(philo->monitor->full))
	{
		safe_mutex_lock(philo->dead_mod);
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
