/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:50:19 by kaan              #+#    #+#             */
/*   Updated: 2024/02/25 23:53:55 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_eat(t_philo *philo, long start)
{
	safe_mutex_lock(philo->fork_r);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	safe_mutex_lock(philo->fork_l);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	philo->last_meal_time = current_time();
	safe_mutex_lock(philo->eat_mod);
	printf("%ld %d  is eating\n", time_stamp(start), philo->id);
	*(philo->monitor->feed_time) += 1;
	safe_mutex_unlock(philo->eat_mod);
	ft_sleep(philo->time_to_eat);
	safe_mutex_unlock(philo->fork_l);
	safe_mutex_unlock(philo->fork_r);
}

int	dead(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philo[i].philo_nbr)
	{
		if (current_time() - monitor->philo[i].last_meal_time
			>= monitor->philo[i].time_to_die)
		{
			safe_mutex_lock(&(monitor->dead_mod));
			monitor->philo[i].dead = 1;
			printf("%d died\n", monitor->philo[i].id);
			return (1);
			safe_mutex_unlock(&(monitor->dead_mod));
		}
		i++;
	}
	return (0);
}

int	food_check(t_monitor *monitor)
{
	if (monitor->philo->food_quantity)
	{
		safe_mutex_lock(&(monitor->eat_mod));
		if (*(monitor->feed_time) - 1 >= monitor->philo->food_quantity + 1)
			return (1);
		safe_mutex_unlock(&(monitor->eat_mod));
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
