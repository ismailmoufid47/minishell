/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:15:28 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// the original memmove segfaults if (!dst && src) or (dst && !src)
// but doesn't if (!dst && !src) and returns dst, bcs it checks if they're not 
// equal before copying
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst != src)
	{
		if (dst > src)
		{
			while (len--)
				((char *)dst)[len] = ((char *)src)[len];
		}
		if (dst < src)
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
