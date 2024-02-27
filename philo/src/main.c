/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 21:58:21 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring(void *data)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)data;
	if (monitor->philo->philo_nbr == 1)
		return (NULL);
	while (1)
	{
		if (dead(monitor) == 1 || food_check(monitor) == 1)
			return (NULL);
	}
	return (NULL);
}

void	*action(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_nbr == 1)
	{
		printf("%ld %d died\n", time_stamp(philo->start), philo->id);
		return (NULL);
	}
	if (philo->id % 2)
		ft_sleep(1);
	while (!dead_loop(philo))
	{
		p_think(philo, philo->start);
		p_eat(philo, philo->start);
		p_sleep(philo, philo->start);
	}
	return (NULL);
}

void	simulation(t_philo philo, t_monitor monitor)
{
	int			i;

	i = 0;
	safe_pthread_create(&(monitor.mon), &monitoring, &monitor);
	while (i < philo.philo_nbr)
	{
		safe_pthread_create(&(monitor.philo[i].ph),
			&action, &(monitor.philo[i]));
		i++;
	}
	i = 0;
	while (i < philo.philo_nbr)
	{
		safe_pthread_join((monitor.philo[i].ph));
		i++;
	}
	safe_pthread_join(monitor.mon);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_monitor		monitor;

	if (check_valid_args(av) == 1)
		return (1);
	if (ac == 5 || ac == 6)
	{
		philo = safe_malloc(sizeof(t_philo));
		monitor.fork = safe_malloc(sizeof(t_fork) * ft_atol(av[1]));
		fork_init(&monitor, av);
		monitor_init(&monitor, philo, av);
		philo_init(philo, &monitor, av);
		simulation(*philo, monitor);
		destroy_all(&monitor, philo);
	}
	else
		printf("Wrong Arguments!\n");
}
