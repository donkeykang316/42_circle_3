/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:48:32 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 18:53:06 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_monitor	t_monitor;

typedef struct s_philo
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				food_quantity;
	int					id;
	pthread_t			ph;
	long				start;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	long				last_meal_time;
	pthread_mutex_t		*eat_mod;
	pthread_mutex_t		*dead_mod;
	t_monitor			*monitor;
}	t_philo;

struct	s_monitor
{
	t_philo				*philo;
	int					*dead;
	pthread_t			mon;
	pthread_mutex_t		eat_mod;
	pthread_mutex_t		dead_mod;
	int					*feed_time;
};

void	*safe_malloc(size_t byte);
long	ft_atol(const char *nptr);
long	current_time(void);
long	time_stamp(long start);
void	ft_sleep(long milsec);
void	input_parse(t_philo *philo, char **av);
void	fork_init(pthread_mutex_t *fork, char **av);
void	monitor_init(t_monitor *monitor, t_philo *philo, char **av);
void	philo_init(t_philo *philo,
			t_monitor *monitor,
			pthread_mutex_t *fork,
			char **av);
void	p_eat(t_philo *philo, long start);
void	p_think(t_philo *philo, long start);
void	p_sleep(t_philo *philo, long start);
void	*monitoring(void *data);
void	*action(void *data);
void	simulation(t_philo philo, t_monitor monitor);
int		dead(t_monitor *monitor);
int		food_check(t_monitor *monitor);
void	safe_pthread_create(pthread_t *thread,
			void*(*routine)(void*), void *arg);
void	safe_pthread_join(pthread_t thread);
void	safe_mutex_init(pthread_mutex_t *mutex);
void	safe_mutex_lock(pthread_mutex_t *mutex);
void	safe_mutex_unlock(pthread_mutex_t *mutex);
void	safe_mutex_destroy(pthread_mutex_t *mutex);
void	mutex_destry_all(t_monitor *monitor);
int		dead_loop(t_philo *philo);

#endif
