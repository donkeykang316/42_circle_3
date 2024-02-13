/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/12 17:55:36 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	input_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void	assign_fork(t_table *table)
{
	t_fork	fork;

	pthread_mutex_init(&fork.fork, NULL);
	table->philo->left = fork;
	table->philo->right = fork;
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
		table->philo[i] = philo;
		table->fork[i] = fork;
		assign_fork(table);
		i++;
	}
}

void	simulation(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	/*while (j < table->philo_nbr)
	{
		table->philo[i].first = table->fork[j];
		j++;
		table->philo[i].second = table->fork[j];
		j++;
		i++;
	}*/

}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac == 5 || ac == 6)
	{
		table = safe_malloc(sizeof(t_table));
		input_parse(table, av);
		philo_init(table);
		//simulation(table);
	}
	else
		printf("Wrong Arguments!\n");
}
