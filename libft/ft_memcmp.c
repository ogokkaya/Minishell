/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:22:00 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/18 19:50:48 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	const unsigned char	*ptr;

	str = ((const unsigned char *)s1);
	ptr = ((const unsigned char *)s2);
	i = 0;
	while (i < n)
	{
		if (!(str[i] == ptr[i]))
			return (str[i] - ptr[i]);
		i++;
	}
	return (0);
}
