/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:49:23 by ogokkaya          #+#    #+#             */
/*   Updated: 2023/12/22 00:55:03 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	unsigned int	sign;
	unsigned int	result;
	int				i;

	i = 0;
	result = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || (s[i] == 32))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	if (s[i] == '-' || s[i] == '+')
		return (0);
	while ((ft_isdigit(s[i])) && s[i] != '\0')
		result = result * 10 + (s[i++] - '0');
	return (sign * result);
}
