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

void	input_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->fork_nbr = table->philo_nbr;
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atol(av[5]);
}

void	philo_init(t_table *table)
{
	t_philo	philo;
	int		i;

	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	i = 0;
	while (i < table->philo_nbr)
	{
		philo.table = table;
		philo.id = i;
		//philo.dead = 0;
		table->philo[i] = philo;
		i++;
	}
}

void	*action(void *data)
{
	struct timeval	time;
	t_philo			*philo;

	philo = (t_philo *)data;
	pthread_mutex_init(&(philo->fork_l), NULL);
	pthread_mutex_init(&(philo->fork_r), NULL);
	gettimeofday(&time, NULL);
	printf("Philosopher%d is thinking\n", philo->id);
	if (philo->table->fork_nbr)
	{
		pthread_mutex_lock(&(philo->fork_l));
		philo->table->fork_nbr -= 1;
	}
	else
		printf("Philosopher%d is sleeping\n", philo->id);
	if (philo->table->fork_nbr)
	{
		pthread_mutex_lock(&(philo->fork_r));
		philo->table->fork_nbr -= 1;
	}
	else
		printf("Philosopher%d is sleeping\n", philo->id);
	usleep(philo->table->time_to_eat);
	printf("Philosopher%d is eating\n", philo->id);
	pthread_mutex_unlock(&(philo->fork_l));
	philo->table->fork_nbr += 1;
	pthread_mutex_unlock(&(philo->fork_r));
	philo->table->fork_nbr += 1;
}

void	simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&(table->philo->ph_id), NULL, action, &(table->philo[i])))
			return ;
		i++;
	}
	if (pthread_join(table->philo->ph_id, NULL))
		return ;
}

int	main(int ac, char **av)
{
	t_table			*table;

	if (ac == 5 || ac == 6)
	{
		table = safe_malloc(sizeof(t_table));
		input_parse(table, av);
		philo_init(table);
		simulation(table);
	}
	else
		printf("Wrong Arguments!\n");
}
