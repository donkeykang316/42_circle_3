/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:21 by kaan              #+#    #+#             */
/*   Updated: 2024/02/25 16:04:24 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

void	*safe_malloc(size_t byte)
{
	void	*ptr;

	ptr = malloc(byte);
	if (!ptr)
	{
		printf("Malloc fail!\n");
		exit(0);
	}
	return (ptr);
}

long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Time error!\n");
		exit(0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	time_stamp(long start)
{
	return (current_time() - start);
}

void	ft_sleep(long milsec)
{
	usleep(milsec * 1000);
}
