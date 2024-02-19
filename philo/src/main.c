/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/19 14:29:51 by kaan             ###   ########.fr       */
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

void	monitor_init(t_monitor *monitor, t_philo philo, char **av)
{
	monitor->philo = &philo;
}

void	philo_init(t_philo *philo, t_monitor *monitor, pthread_mutex_t *fork, char **av)
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
		philo->fork_l = &fork[i];
		if (!i)
			philo->fork_r = &fork[philo->philo_nbr - 1];
		else
			philo->fork_r = &fork[i - 1];
		philo->last_meal_time = 0;
		monitor->philo[i] = *philo;
		i++;
	}
}

void	p_eat(t_philo *philo, long start)
{
	pthread_mutex_lock(philo->fork_r);
	printf("%ld Philosopher%d has taken a fork\n", time_stamp(start), philo->id);
	pthread_mutex_lock(philo->fork_l);
	if (current_time() - philo->last_meal_time >= philo->time_to_die && philo->feed == 0)
	{
		philo->dead = 1;
		printf("%ld Philosopher%d died\n", time_stamp(start), philo->id);
		exit(0) ;
	}
	printf("%ld Philosopher%d has taken a fork\n", time_stamp(start), philo->id);
	printf("%ld Philosopher%d  is eating\n", time_stamp(start), philo->id);
	philo->feed = 1;
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	philo->last_meal_time = current_time();
}

void	p_think(t_philo *philo, long start)
{
	if (philo->id % 2 == 0 && philo->last_meal_time - current_time() < 1)
	{
		printf("%ld Philosopher%d is thinking\n", time_stamp(start), philo->id);
		usleep(5);
		philo->last_meal_time = current_time();
	}
}

void	p_sleep(t_philo *philo, long start)
{
	printf("%ld Philosopher%d is sleeping\n", time_stamp(start), philo->id);
	usleep(philo->time_to_sleep);
	philo->last_meal_time = current_time();
}

void	*action(void *data)
{
	t_philo	*philo;
	long	start;

	philo = (t_philo *)data;
	start = current_time();
	philo->last_meal_time = current_time();
	while (1)
	{
		p_think(philo, start);
		p_eat(philo, start);
		p_sleep(philo, start);
	}
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
	t_philo			*philo;
	t_monitor		monitor;
	pthread_mutex_t	*fork;

	if (ac == 5 || ac == 6)
	{
		philo = safe_malloc(sizeof(t_philo));
		fork = safe_malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
		fork_init(fork, av);
		monitor_init(&monitor, *philo, av);
		philo_init(philo, &monitor, fork, av);
		simulation(*philo, &monitor);
		free(monitor.philo);
		free(philo);
	}
	else
		printf("Wrong Arguments!\n");
}
