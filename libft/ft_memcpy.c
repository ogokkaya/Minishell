/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:51:16 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/19 00:54:16 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (!dst && !src)
		return (0);
	if (dst == src)
		return (dst);
	str = dst;
	while (i < n)
	{
		*((unsigned char *)&dst[i]) = *((unsigned char *)&src[i]);
		i++;
	}
	return (str);
}
