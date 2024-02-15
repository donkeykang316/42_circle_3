/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:48:32 by kaan              #+#    #+#             */
/*   Updated: 2024/02/15 21:40:52 by kaan             ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		last_meal_time;
	pthread_t	ph_id;
	t_fork		*left;
	t_fork		*right;
	t_table		*table;
}	t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	pthread_t		monitor;
	t_philo			*philo;
	t_fork			*fork;
	pthread_mutex_t	t_mutex;
};

void	*safe_malloc(size_t byte);
long	ft_atol(const char *nptr);

#endif
