/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:04:07 by vgalmich          #+#    #+#             */
/*   Updated: 2024/06/13 17:22:46 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_unsigned(unsigned int value, int *counter)
{
	if (value >= 10)
		ft_print_unsigned(value / 10, counter);
	ft_putchar_fd(value % 10 + '0', 1);
	(*counter)++;
}
