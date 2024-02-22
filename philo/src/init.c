/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:52:01 by kaan              #+#    #+#             */
/*   Updated: 2024/02/22 16:12:47 by kaan             ###   ########.fr       */
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
}

void	fork_init(pthread_mutex_t *fork, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atol(av[1]))
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	monitor_init(t_monitor *monitor, t_philo *philo, char **av)
{
	monitor->philo = philo;
}

void	philo_init(t_philo *philo, 
		t_monitor *monitor,
		pthread_mutex_t *fork,
		char **av)
{
	int				i;

	monitor->philo = safe_malloc(sizeof(t_philo) * ft_atol(av[1]));
	i = 0;
	while (i < ft_atol(av[1]))
	{
		input_parse(philo, av);
		philo->id = i + 1;
		philo->dead = 0;
		philo->feed = 0;
		philo->feed_time = 0;
		philo->fork_l = &fork[i];
		if (!i)
			philo->fork_r = &fork[philo->philo_nbr - 1];
		else
			philo->fork_r = &fork[i - 1];
		pthread_mutex_init(&(philo->eat_mod), NULL);
		philo->last_meal_time = current_time();
		philo->start = current_time();
		monitor->philo[i] = *philo;
		i++;
	}
}