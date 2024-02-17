/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/15 23:27:31 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	input_parse(t_monitor *monitor, char **av)
{
	monitor->philo_nbr = ft_atol(av[1]);
	monitor->time_to_die = ft_atol(av[2]);
	monitor->time_to_eat = ft_atol(av[3]);
	monitor->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		monitor->eat_times = ft_atol(av[5]);
}

void	monitor_init(t_monitor *monitor)
{
	t_philo			*philo;
	struct timeval	time;

	monitor->philo = safe_malloc(sizeof(t_philo) * monitor->philo_nbr);
	philo = safe_malloc(sizeof(t_philo));
	philo->monitor = monitor;
	monitor->philo = philo;
	philo->id = 0;
	philo->dead = 0;
	pthread_mutex_init(&(philo->fork_l), NULL);
	pthread_mutex_init(&(philo->fork_r), NULL);
	gettimeofday(&time, NULL);
	philo->last_meal_time = time.tv_usec;
}

void	*action(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("error:%ld\n", philo->monitor->time_to_eat);
	printf("Philosopher%d eats\n", philo->id);
	//usleep(philo->monitor->time_to_eat);
	printf("Philosopher%d finishs\n", philo->id);
	return (NULL);
}

void	simulation(t_monitor *monitor)
{
	int			i;

	i = 0;
	//pass two structures to each other possible?
	while (i < monitor->philo_nbr)
	{
		monitor->philo[i].id = i;
		if (pthread_create(&(monitor->philo[i].ph), NULL, action, &(monitor->philo[i])))
			return ;
		i++;
	}
	i = 0;
	while (i < monitor->philo_nbr)
	{
		if (pthread_join((monitor->philo[i].ph), NULL))
			return ;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_monitor	*monitor;

	if (ac == 5 || ac == 6)
	{
		monitor = safe_malloc(sizeof(t_monitor));
		input_parse(monitor, av);
		monitor_init(monitor);
		simulation(monitor);
		free(monitor);
	}
	else
		printf("Wrong Arguments!\n");
}
