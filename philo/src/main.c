/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:02 by kaan              #+#    #+#             */
/*   Updated: 2024/02/09 00:43:28 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*eat_food(void *data)
{
	printf("Philosopher get ready\n");
	sleep(2);
	printf("Philosopher is eating\n");
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	philo[5];
	int			i;
	int			x;
	int			y;

	i = 0;
	while (i != 5)
	{
		pthread_create(&philo[i], NULL, eat_food, NULL);
		i++;
	}
	i = 0;
	while (i != 5)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
}
