/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:23:37 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 22:04:52 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
	{
		printf("Mutex destroy fail!\n");
		exit(0);
	}
}

int	dead_loop(t_philo *philo)
{
	if (philo->id == 1 && *(philo->monitor->dead))
	{
		safe_mutex_lock(&(philo->monitor->dead_mod));
		printf("%ld %d died\n", time_stamp(philo->start), philo->id);
		return (safe_mutex_unlock(&(philo->monitor->dead_mod)), 1);
	}
	else if (*(philo->monitor->dead))
		return (1);
	if (*(philo->monitor->full))
	{
		safe_mutex_lock(philo->dead_mod);
		return (safe_mutex_unlock(philo->dead_mod), 1);
	}
	return (0);
}

void	destroy_all(t_monitor *monitor,
			t_philo *philo)
{
	long	i;

	i = 0;
	while (i < monitor->philo->philo_nbr)
	{
		safe_mutex_destroy(&(monitor->fork[i].fork));
		safe_mutex_destroy(monitor->philo[i].eat_mod);
		i++;
	}
	free(monitor->dead);
	free(monitor->full);
	free(monitor->feed_time);
	free(monitor->fork);
	free(philo);
	free(monitor->philo);
}

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **av)
{
	if (ft_atol(av[1]) <= 0 || check_arg_content(av[1]) == 1)
		return (printf("Wrong argument\n"), 1);
	if (ft_atol(av[2]) <= 0 || check_arg_content(av[2]) == 1)
		return (printf("Wrong argument\n"), 1);
	if (ft_atol(av[3]) <= 0 || check_arg_content(av[3]) == 1)
		return (printf("Wrong argument\n"), 1);
	if (ft_atol(av[4]) <= 0 || check_arg_content(av[4]) == 1)
		return (printf("Wrong argument\n"), 1);
	if (av[5] && (ft_atol(av[5]) < 0 || check_arg_content(av[5]) == 1))
		return (printf("Wrong argument\n"), 1);
	return (0);
}
