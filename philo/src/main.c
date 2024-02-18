/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/18 13:22:33 by kaan             ###   ########.fr       */
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
		philo->eat_times = ft_atol(av[5]);
}

void	monitor_init(t_monitor *monitor, t_philo philo, char **av)
{
	monitor->philo = &philo;
}

void	philo_init(t_philo *philo, t_monitor *monitor, char **av)
{
	struct timeval	time;
	int				i;

	gettimeofday(&time, NULL);
	monitor->philo = safe_malloc(sizeof(t_philo) * ft_atol(av[1]));
	i = 0;
	while (i < ft_atol(av[1]))
	{
		input_parse(philo, av);
		philo->id = i + 1;
		philo->dead = 0;
		pthread_mutex_init(&(philo->fork_l), NULL);
		pthread_mutex_init(&(philo->fork_r), NULL);
		philo->last_meal_time = time.tv_usec;
		monitor->philo[i] = *philo;
		i++;
	}
}

void	*action(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	printf("Philosopher%d eats\n", philo->id);
	usleep(philo->time_to_eat);
	printf("Philosopher%d finishs\n", philo->id);
	return (NULL);
}

void	simulation(t_philo philo, t_monitor *monitor)
{
	int			i;

	i = 0;
	while (i < philo.philo_nbr)
	{
		if (pthread_create(&(monitor->philo[i].ph), NULL, &action, &(monitor->philo[i])))
			return ;
		i++;
	}
	i = 0;
	while (i < philo.philo_nbr)
	{
		if (pthread_join((monitor->philo[i].ph), NULL))
			return ;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_monitor	monitor;

	if (ac == 5 || ac == 6)
	{
		philo = safe_malloc(sizeof(t_philo));
		monitor_init(&monitor, *philo, av);
		philo_init(philo, &monitor, av);
		simulation(*philo, &monitor);
		free(monitor.philo);
		free(philo);
	}
	else
		printf("Wrong Arguments!\n");
}
