/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:26:54 by kaan              #+#    #+#             */
/*   Updated: 2024/01/28 12:27:38 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putnbr_printf(long n, int *count)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		ft_putnbr_printf(n, count);
		(*count)++;
	}
	else if (n > 9)
	{
		ft_putnbr_printf(n / 10, count);
		ft_putnbr_printf(n % 10, count);
	}
	else
	{
		c = n + 48;
		write(1, &c, 1);
		(*count)++;
	}
	return (0);
}
