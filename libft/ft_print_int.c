/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:03 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/13 17:22:20 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_numlen(int value)
{
	size_t	total;

	total = 0;
	if (value <= 0)
		total++;
	while (value)
	{
		total++;
		value = value / 10;
	}
	return (total);
}

void	ft_print_int(int value, int *counter)
{
	ft_putnbr_fd(value, 1);
	(*counter) += ft_numlen(value);
}
