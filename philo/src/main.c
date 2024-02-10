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

void	*eat_food(void *id)
{
	//t_fork	fork;
	int		i;	

	i = *(int *)id;
	printf("Philosopher%d takes the fork\n", i);
	//pthread_mutex_lock(&fork.fork);
	sleep(1);
	printf("Philosopher%d finishs the food\n", i);
	//pthread_mutex_unlock(&fork.fork);
	free(id);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	*philo;
	t_fork		fork;
	int			*id;
	int			i;

	//pthread_mutex_init(&fork.fork, NULL);
	i = 1;
	philo = malloc(10 * sizeof(pthread_t));
	while (i != 11)
	{
		id = malloc(sizeof(int));
		if (!id)
			return (0);
		*id = i;
		if (pthread_create(philo, NULL, eat_food, id))
			return (0);
		/*pthread_detach(philo[3]);
		pthread_detach(philo[4]);*/
		i++;
	}
	if (pthread_join(*philo, NULL))
		return (0);
	//pthread_mutex_destroy(&fork.fork);
	free(philo);
	pthread_exit(0);
}
