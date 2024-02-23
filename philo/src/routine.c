/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:50:19 by kaan              #+#    #+#             */
/*   Updated: 2024/02/22 16:17:25 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_eat(t_philo *philo, long start)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_r);
		printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	}
	pthread_mutex_lock(philo->fork_l);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	philo->last_meal_time = current_time();
	printf("%ld %d  is eating\n", time_stamp(start), philo->id);
	philo->feed_time += 1;
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	dead(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philo->philo_nbr)
	{
		if (current_time() - monitor->philo->last_meal_time >= monitor->philo->time_to_die)
		{
			monitor->philo->dead = 1;
			printf("%d died\n", monitor->philo->id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	p_think(t_philo *philo, long start)
{
	printf("%ld %d is thinking\n", time_stamp(start), philo->id);
}

void	p_sleep(t_philo *philo, long start)
{
	printf("%ld %d is sleeping\n", time_stamp(start), philo->id);
	ft_sleep(philo->time_to_sleep);
}
