/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:56 by kaan              #+#    #+#             */
/*   Updated: 2024/02/26 22:08:05 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	safe_pthread_create(pthread_t *thread,
			void *(*routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg))
	{
		printf("Thread init fail!\n");
		exit(0);
	}
}

void	safe_pthread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL))
		return ;
}

void	safe_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		printf("Mutex init fail!\n");
		exit(0);
	}
}

void	safe_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		printf("Mutex lock fail!\n");
		exit(0);
	}
}

void	safe_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
	{
		printf("Mutex unlock fail!\n");
		exit(0);
	}
}
