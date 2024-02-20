/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:48:32 by kaan              #+#    #+#             */
/*   Updated: 2024/02/20 15:22:46 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				food_quantity;
	int					id;
	int					dead;
	int					feed;
	int					feed_time;
	pthread_t			ph;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	long				last_meal_time;
}	t_philo;

typedef struct s_monitor 
{
	t_philo		*philo;
	pthread_t	mon;
}	t_monitor;


void	*safe_malloc(size_t byte);
long	ft_atol(const char *nptr);
long	current_time(void);
long	time_stamp(long start);

#endif
