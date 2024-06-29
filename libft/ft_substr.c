/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:05:23 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/18 19:43:36 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	end;

	if (!s && len == 0)
		return (ft_strdup(""));
	end = ft_strlen(s);
	if (end <= start)
		return (ft_strdup(""));
	if (len > end - start)
		len = end - start;
	j = 0;
	i = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i + start] && i < len)
	{
		result[j] = s[i + start];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
