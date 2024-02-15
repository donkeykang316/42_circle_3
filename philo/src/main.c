/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/15 22:54:24 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	input_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atol(av[5]);
}

void	assign_fork(t_table *table, int i)
{
	t_fork	*fork;

	pthread_mutex_init(&(fork->fork), NULL);
	table->philo->left = &fork[i];
	table->philo->right = &fork[i + 1];
	//cotinue from here, draw a plan for continuation
}

void	philo_init(t_table *table)
{
	t_philo	philo;
	t_fork	fork;
	int		i;

	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	i = 0;
	while (i < table->philo_nbr)
	{
		philo.table = table;
		philo.id = i;
		fork.id = i;
		table->philo[i] = philo;
		table->fork[i] = fork;
		assign_fork(table, i);
		i++;
	}
}

void	*action(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	printf("Philosopher%d is thinking\n", philo->id);
	//pthread_mutex_lock(&(philo->left->fork));
	//pthread_mutex_lock(&(philo->right->fork));
	usleep(philo->table->time_to_eat);
	printf("Philosopher%d is eating\n", philo->id);
	//pthread_mutex_unlock(&(philo->left->fork));
	//pthread_mutex_unlock(&(philo->right->fork));
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
