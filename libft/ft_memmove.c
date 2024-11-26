/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:11:45 by vgalmich          #+#    #+#             */
/*   Updated: 2024/05/28 14:13:47 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*temp;

	temp = (const unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (temp < dst)
	{
		while (n--)
			dst[n] = temp[n];
	}
	else
		ft_memcpy(dst, temp, n);
	return (dest);
}
