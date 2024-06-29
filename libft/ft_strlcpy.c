/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:34:06 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/22 00:49:35 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	if (dstsize)
	{
		while (index < (dstsize - 1) && src[index])
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	while (src[index])
		index++;
	return (index);
}
