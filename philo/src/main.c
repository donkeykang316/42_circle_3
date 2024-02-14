/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/14 14:02:50 by kaan             ###   ########.fr       */
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

	i = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		philo.id = i;
		fork.id = i;
		table->philo[i] = philo;
		table->fork[i] = fork;
		philo.table = table;
		assign_fork(table, i);
		i++;
	}
}

void	*action(void *data)
{
	struct timeval	time;
	t_philo			*philo;

	philo = (t_philo *)data;
	philo->last_meal_time = gettimeofday(&time, NULL);
	printf("Philosopher%d is thinking\n", philo->id);
	//pthread_mutex_lock(&(philo->left->fork));
	//pthread_mutex_lock(&(philo->right->fork));
	usleep(philo->table->time_to_eat);
	printf("now:%ld\n", gettimeofday(&time, NULL));
	printf("last:%lu\n", philo->last_meal_time);
	printf("die:%lu\n", philo->table->time_to_die);
	if (gettimeofday(&time, NULL) - philo->last_meal_time == philo->table->time_to_die)
	{
		printf("Philosopher%d is dead\n", philo->id);
		pthread_detach(philo->ph_id);
	}
	printf("Philosopher%d is eating\n", philo->id);
	usleep(philo->table->time_to_eat);
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
	t_table	*table;
	struct timeval	time;

	printf("time:%ld\n", gettimeofday(&time, NULL));

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
