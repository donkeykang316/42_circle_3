/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_handle_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:55:14 by kaan              #+#    #+#             */
/*   Updated: 2024/01/28 12:28:04 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	handle_c(char c, va_list args)
{
	char	var;
	int		count;

	count = 0;
	(void)c;
	var = va_arg(args, int);
	count = ft_putchar_printf(var);
	return (count);
}

int	handle_s(char c, va_list args)
{
	char	*var;
	int		count;

	count = 0;
	(void)c;
	var = va_arg(args, char *);
	count = ft_putstr_printf(var);
	return (count);
}

int	handle_p(char c, va_list args)
{
	void	*var;
	int		count;

	count = 0;
	(void)c;
	var = va_arg(args, void *);
	if (!var)
	{
		ft_putstr_printf("(nil)");
		return (5);
	}
	ft_putstr_printf("0x");
	ft_putaddress((unsigned long long int)var, &count);
	return (count + 2);
}

int	handle_d_i(char c, va_list args)
{
	int	var;
	int	count;

	count = 0;
	(void)c;
	var = va_arg(args, int);
	ft_putnbr_printf(var, &count);
	return (count);
}

int	handle_u(char c, va_list args)
{
	unsigned int	var;
	int				count;

	count = 0;
	(void)c;
	var = va_arg(args, unsigned int);
	ft_putnbr_printf(var, &count);
	return (count);
}
