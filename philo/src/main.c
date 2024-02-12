/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/12 14:31:13 by kaan             ###   ########.fr       */
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

/*void	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = table->philo_nbr;
	while (i)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return ;
		philo->id = i;
		table->philo = philo;
		i--;
	}
}*/

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac == 5 || ac == 6)
	{
		table = malloc(sizeof(t_table));
		if (!table)
			return (0);
		input_parse(table, av);
		philo_init(table);
		printf("%d\n", table->philo->id);
	}
	else
		printf("Wrong Arguments!\n");
}
