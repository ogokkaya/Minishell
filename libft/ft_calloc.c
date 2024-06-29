/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:37:56 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/19 00:17:05 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	i = -1;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (++i, i < count * size)
		((char *)p)[i] = 0;
	return (p);
}
