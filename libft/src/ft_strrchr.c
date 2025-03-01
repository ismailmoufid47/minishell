/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:10 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	c = (unsigned char)c;
	i = ft_strlen(s);
	if (!c)
		return ((char *)&s[i]);
	while (i--)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
