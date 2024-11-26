/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:33:49 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/13 17:22:13 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexa(unsigned int num, const char c)
{
	if (num >= 16)
	{
		ft_puthexa(num / 16, c);
		ft_puthexa(num % 16, c);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else if (c == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

size_t	ft_hexalen(unsigned int value)
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

void	ft_print_hexa(unsigned int value, const char c, int *counter)
{
	if (value == 0)
		(*counter) += (write(1, "0", 1));
	else
		ft_puthexa(value, c);
	(*counter) += ft_hexalen(value);
}
