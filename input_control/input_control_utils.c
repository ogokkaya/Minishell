/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:54:39 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/06 20:30:59 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

void	j_0c_null(t_variables *vars, char **line)
{
	vars->j = 0;
	vars->c = '\0';
	(*line)++;
}

void	j_1i_0(t_variables *vars)
{
	vars->j = 1;
	vars->i = 0;
}

int	in_out_check(t_variables *vars, char *line)
{
	if ((vars->c == REDIRECT_OUT && *line == REDIRECT_IN)
		|| (vars->c == REDIRECT_IN && *line == REDIRECT_OUT))
		return (FALSE);
	return (TRUE);
}
