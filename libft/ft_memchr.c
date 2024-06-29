/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:55:15 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/22 00:48:38 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*str;

	str = ((unsigned char *)s);
	i = 0;
	while (n > 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
		n--;
	}
	return (NULL);
}
