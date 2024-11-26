/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:28 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/13 17:22:29 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_putptr(num / 16);
		ft_putptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

size_t	ft_ptrlen(uintptr_t value)
{
	size_t	total;

	total = 0;
	while (value)
	{
		total++;
		value = value / 16;
	}
	return (total);
}

void	ft_print_pointer(unsigned long long value, int *counter)
{
	if (value == 0)
		(*counter) += (write(1, "(nil)", 5));
	else
	{
		(*counter) += write(1, "0x", 2);
		ft_putptr(value);
		(*counter) += ft_ptrlen(value);
	}
}
