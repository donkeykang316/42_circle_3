/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:48:32 by kaan              #+#    #+#             */
/*   Updated: 2024/02/15 23:22:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				dead;
	pthread_t		ph_id;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	t_table			*table;
}	t_philo;

struct s_table
{
	long			philo_nbr;
	long			fork_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	pthread_t		monitor;
	t_philo			*philo;
	pthread_mutex_t	t_mutex;
};

void	*safe_malloc(size_t byte);
long	ft_atol(const char *nptr);

#endif
