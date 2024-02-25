/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 00:02:09 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring(void *data)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)data;
	while (1)
	{
		if (dead(monitor) == 1 || food_check(monitor) == 1)
			exit(0);
	}
	return (NULL);
}

void	*action(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		ft_sleep(1);
	while (1)
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
	safe_pthread_create(&(monitor.mon), monitoring, &monitor);
	while (i < philo.philo_nbr)
	{
		safe_pthread_create(&(monitor.philo->ph), &action, &(monitor.philo[i]));
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
	pthread_mutex_t	*fork;

	if (ac == 5 || ac == 6)
	{
		philo = safe_malloc(sizeof(t_philo));
		fork = safe_malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
		fork_init(fork, av);
		monitor_init(&monitor, philo, av);
		philo_init(philo, &monitor, fork, av);
		simulation(*philo, monitor);
		mutex_destry_all(&monitor);
		free(monitor.philo);
		free(philo);
	}
	else
		printf("Wrong Arguments!\n");
}
