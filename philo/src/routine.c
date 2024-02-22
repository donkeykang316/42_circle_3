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
	pthread_mutex_lock(philo->fork_r);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	pthread_mutex_lock(philo->fork_l);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
    philo->feed = 1;
	printf("%ld %d  is eating\n", time_stamp(start), philo->id);
    pthread_mutex_lock(&(philo->eat_mod));
	philo->feed_time += 1;
    philo->last_meal_time = current_time();
     pthread_mutex_unlock(&(philo->eat_mod));
	ft_sleep(philo->time_to_eat);
	philo->feed = 0;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

int	dead(t_philo *philo)
{
	if (current_time() - philo->last_meal_time >= philo->time_to_die && !philo->feed)
	{
		philo->dead = 1;
		printf("%d died\n", philo->id);
		return (1);
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
