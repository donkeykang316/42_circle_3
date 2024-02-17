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

typedef struct s_monitor t_monitor;

typedef struct s_philo
{
	int					id;
	int					dead;
	pthread_t			ph;
	pthread_mutex_t		fork_l;
	pthread_mutex_t		fork_r;
	long				last_meal_time;
	struct s_monitor	*monitor;
}	t_philo;

struct s_monitor
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eat_times;
	t_philo	*philo;
};


void	*safe_malloc(size_t byte);
long	ft_atol(const char *nptr);

#endif
