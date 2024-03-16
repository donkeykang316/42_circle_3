/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:49:27 by someng            #+#    #+#             */
/*   Updated: 2024/01/28 12:27:30 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_puthex(long n, int *count)
{
	if (n < 0)
	{
		write(1, "-", 1);
		ft_puthex(-n, count);
		(*count)++;
	}
	else if (n >= 16)
	{
		ft_puthex(n / 16, count);
		ft_puthex(n % 16, count);
	}
	else
	{
		if (n < 10)
		{
			ft_putchar_printf(n + 48);
			(*count)++;
		}
		else
		{
			ft_putchar_printf(n + 97 - 10);
			(*count)++;
		}
	}
	return (0);
}

int	ft_puthex_up(long n, int *count)
{
	if (n < 0)
	{
		write(1, "-", 1);
		ft_puthex_up(-n, count);
		(*count)++;
	}
	else if (n >= 16)
	{
		ft_puthex_up(n / 16, count);
		ft_puthex_up(n % 16, count);
	}
	else
	{
		if (n < 10)
		{
			ft_putchar_printf(n + 48);
			(*count)++;
		}
		else
		{
			ft_putchar_printf(n + 87 - 32);
			(*count)++;
		}
	}
	return (0);
}

int	ft_putaddress(unsigned long long int n, int *count)
{
	if (n >= 16)
	{
		ft_puthex(n / 16, count);
		ft_puthex(n % 16, count);
	}
	else
	{
		if (n < 10)
		{
			ft_putchar_printf(n + 48);
			(*count)++;
		}
		else
		{
			ft_putchar_printf(n + 97 - 10);
			(*count)++;
		}
	}
	return (0);
}
