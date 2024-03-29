/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:50:19 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 19:28:20 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_eat(t_philo *philo, long start)
{
	safe_mutex_lock(philo->fork_r);
	safe_mutex_lock(&(philo->print));
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	safe_mutex_unlock(&(philo->print));
	safe_mutex_lock(philo->fork_l);
	safe_mutex_lock(&(philo->print));
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	safe_mutex_unlock(&(philo->print));
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
	while (i < monitor->philo[0].philo_nbr)
	{
		if (current_time() - monitor->philo[i].last_meal_time
			>= monitor->philo[i].time_to_die)
		{
			safe_mutex_lock(&(monitor->dead_mod));
			*(monitor->dead) = 1;
			return (safe_mutex_unlock(&(monitor->dead_mod)), 1);
		}
		i++;
	}
	return (0);
}

int	food_check(t_monitor *monitor)
{
	if (monitor->philo[0].food_quantity == -1)
		return (0);
	else
	{
		if (*(monitor->feed_time)
			>= (monitor->philo[0].food_quantity + 1)
			* monitor->philo[0].philo_nbr)
		{
			safe_mutex_lock(&(monitor->eat_mod));
			*(monitor->full) = 1;
			return (safe_mutex_unlock(&(monitor->eat_mod)), 1);
		}
	}
	return (0);
}

void	p_think(t_philo *philo, long start)
{
	safe_mutex_lock(&(philo->print));
	printf("%ld %d is thinking\n", time_stamp(start), philo->id);
	safe_mutex_unlock(&(philo->print));
}

void	p_sleep(t_philo *philo, long start)
{
	safe_mutex_lock(&(philo->print));
	printf("%ld %d is sleeping\n", time_stamp(start), philo->id);
	safe_mutex_unlock(&(philo->print));
	ft_sleep(philo->time_to_sleep);
}
