/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:27:37 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/20 15:40:01 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checktype(const char c, va_list value, int *counter)
{
	if (c == 'c')
	{
		++(*counter);
		ft_putchar_fd(va_arg(value, int), 1);
	}
	else if (c == 's')
		ft_print_string(va_arg(value, char *), counter);
	else if (c == 'p')
		ft_print_pointer(va_arg(value, unsigned long long), counter);
	else if (c == 'i' || c == 'd')
		ft_print_int(va_arg(value, int), counter);
	else if (c == 'u')
		ft_print_unsigned(va_arg(value, unsigned int), counter);
	else if (c == 'x' || c == 'X')
		ft_print_hexa(va_arg(value, unsigned int), c, counter);
	else if (c != '0')
	{
		++(*counter);
		ft_putchar_fd(c, 1);
	}
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	args;

	counter = 0;
	va_start(args, str);
	if (str == 0)
		return (-1);
	while (*str)
	{
		if (*str != '%')
		{
			ft_putchar_fd(*str, 1);
			counter++;
		}
		else
			ft_checktype(*++str, args, &counter);
		++str;
	}
	va_end(args);
	return (counter);
}
