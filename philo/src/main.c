/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/09 19:44:16 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*eat_food(void *data)
{
	t_fork			fork;

	pthread_mutex_lock(&fork.fork);
	sleep(2);
	pthread_mutex_unlock(&fork.fork);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t		philo[10];
	t_fork			fork;
	int				i;

	pthread_mutex_init(&fork.fork, NULL);
	i = 1;
	while (i != 11)
	{
		if (pthread_create(&philo[i], NULL, eat_food, NULL))
			exit(0);
		printf("Philosopher%d takes the fork\n", i);
		i++;
	}
	i = 1;
	while (i != 11)
	{
		if (pthread_join(philo[i], NULL))
			exit(0);
		printf("Philosopher%d finishs the food\n", i);
		i++;
	}
	pthread_mutex_destroy(&fork.fork);
}
