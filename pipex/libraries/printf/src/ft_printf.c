/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:55:14 by kaan              #+#    #+#             */
/*   Updated: 2024/01/28 12:27:16 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	specifier(char ch, va_list args)
{
	int	count;

	count = 0;
	if (ch == 'c')
		count += handle_c(ch, args);
	else if (ch == 's')
		count += handle_s(ch, args);
	else if (ch == 'p')
		count += handle_p(ch, args);
	else if (ch == 'd' || ch == 'i')
		count += handle_d_i(ch, args);
	else if (ch == 'u')
		count += handle_u(ch, args);
	else if (ch == 'x')
		count += handle_lx(ch, args);
	else if (ch == 'X')
		count += handle_ux(ch, args);
	else
	{
		count += ft_putchar_printf(ch);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, format);
	while (i < ft_strlen_printf(format))
	{
		if (format[i] == '%')
		{
			i++;
			j += specifier(format[i], args);
		}
		else
			j += ft_putchar_printf(format[i]);
		i++;
	}
	va_end(args);
	return (j);
}
