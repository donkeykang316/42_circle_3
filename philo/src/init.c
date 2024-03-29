/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:52:01 by kaan              #+#    #+#             */
/*   Updated: 2024/02/27 20:00:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	input_parse(t_philo *philo, char **av)
{
	philo->philo_nbr = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philo->food_quantity = ft_atol(av[5]);
	else
		philo->food_quantity = -1;
}

void	fork_init(t_monitor *monitor, char **av)
{
	long	i;

	i = 0;
	while (i < ft_atol(av[1]))
	{
		safe_mutex_init(&(monitor->fork[i].fork));
		i++;
	}
}

void	monitor_init(t_monitor *monitor, t_philo *philo)
{
	monitor->philo = philo;
	monitor->dead = safe_malloc(sizeof(int));
	*(monitor->dead) = 0;
	monitor->feed_time = safe_malloc(sizeof(int));
	*(monitor->feed_time) = 0;
	monitor->full = safe_malloc(sizeof(int));
	*(monitor->full) = 0;
	safe_mutex_init(&(monitor->eat_mod));
	safe_mutex_init(&(monitor->dead_mod));
}

void	philo_init(t_philo *philo,
		t_monitor *monitor,
		char **av)
{
	int				i;

	monitor->philo = safe_malloc(sizeof(t_philo) * ft_atol(av[1]));
	i = 0;
	while (i < ft_atol(av[1]))
	{
		input_parse(philo, av);
		philo->id = i + 1;
		philo->fork_l = &(monitor->fork[i].fork);
		if (!i)
			philo->fork_r = &(monitor->fork[philo->philo_nbr - 1].fork);
		else
			philo->fork_r = &(monitor->fork[i - 1].fork);
		philo->last_meal_time = current_time();
		philo->start = current_time();
		safe_mutex_init(&(philo->print));
		philo->eat_mod = &(monitor->eat_mod);
		philo->dead_mod = &(monitor->dead_mod);
		philo->monitor = monitor;
		monitor->philo[i] = *philo;
		i++;
	}
}
