/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/20 20:56:09 by kaan             ###   ########.fr       */
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
		philo->last_meal_time = 0;
		monitor->philo[i] = *philo;
		i++;
	}
}

void	p_eat(t_philo *philo, long start)
{
	pthread_mutex_lock(philo->fork_r);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	pthread_mutex_lock(philo->fork_l);
	printf("%ld %d has taken a fork\n", time_stamp(start), philo->id);
	printf("%ld %d  is eating\n", time_stamp(start), philo->id);
	philo->feed = 1;
	philo->feed_time += 1;
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	philo->last_meal_time = current_time();
}

/*void	dead(t_philo *philo)
{
	if (current_time() - philo->last_meal_time >= philo->time_to_die && !philo->feed)
	{
		philo->dead = 1;
		printf("%ld %d died\n", time_stamp(start), philo->id);
		exit (0);
	}
}*/

void	p_think(t_philo *philo, long start)
{
	printf("%ld %d is thinking\n", time_stamp(start), philo->id);
}

void	p_sleep(t_philo *philo, long start)
{
	philo->feed = 0;
	printf("%ld %d is sleeping\n", time_stamp(start), philo->id);
	ft_sleep(philo->time_to_sleep);
}

void	*monitoring(void *data)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)data;
	if (monitor->philo->dead == 1)
		exit(0);
	return (NULL);
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

void	simulation(t_philo philo, t_monitor monitor)
{
	int			i;

	i = 0;
	if (pthread_create(&(monitor.mon), NULL, monitoring, &monitor))
		return ;
	while (i < philo.philo_nbr)
	{
		if (pthread_create(&(monitor.philo->ph), NULL, &action, &(monitor.philo[i])))
			return ;
		i++;
	}
	i = 0;
	while (i < philo.philo_nbr)
	{
		if (pthread_join((monitor.philo[i].ph), NULL))
			return ;
		i++;
	}
	if (pthread_join(monitor.mon, NULL))
		return ;
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
		free(monitor.philo);
		free(philo);
	}
	else
		printf("Wrong Arguments!\n");
}
