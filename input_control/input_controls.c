/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:10:33 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:01:10 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	quoter(char *line)
{
	static char	quotes_flag;
	int			quote_status;

	quote_status = 0;
	quotes_flag = '\0';
	while (*line != '\0')
	{
		if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
		{
			if (quote_status == 0)
			{
				quotes_flag = *line;
				quote_status = 1;
			}
			else if (quotes_flag == *line)
				quote_status = 0;
		}
		line++;
	}
	if (quote_status == 1)
		return (*exit_status() = 1, FALSE);
	return (TRUE);
}

static int	redirection_check(char *line)
{
	t_variables	vars;

	vars = (t_variables){0};
	while (*line)
	{
		if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
			vars.i = !vars.i;
		if (!vars.i && (*line == REDIRECT_OUT || *line == REDIRECT_IN))
		{
			if (in_out_check(&vars, line))
				return (FALSE);
			if (++vars.j >= 3)
				return (FALSE);
			vars.c = *line;
			while (*++line && ft_space(*line))
				;
		}
		else
			j_0c_null(&vars, &line);
		vars.k++;
	}
	if ((vars.k == 1 || vars.k == 2) && (vars.j == 1 || vars.j == 2))
		return (*exit_status() = 1, FALSE);
	return (TRUE);
}

static int	pipe_check(char *line)
{
	t_variables	vars;

	vars = (t_variables){0};
	while (*line)
	{
		if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
			vars.k = !vars.k;
		if (!vars.k && *line == PIPE)
		{
			if (vars.i > 0 && !vars.j)
				return (*exit_status() = 1, FALSE);
			vars.i++;
			vars.j = 0;
			while (*++line && ft_space(*line))
				;
			if (*line == PIPE)
				return (*exit_status() = 1, FALSE);
			continue ;
		}
		else if (!ft_space(*(line++)))
			j_1i_0(&vars);
	}
	if (vars.i > 0 && !vars.j)
		return (*exit_status() = 1, FALSE);
	return (TRUE);
}

static int	standardizer(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (line[i] == SPACE)
	{
		while (line[i] == SPACE)
			i--;
		if (line[i] == PIPE)
			return (*exit_status() = 1, FALSE);
	}
	if (*line == SPACE || *line == PIPE)
	{
		while (*line == SPACE)
			line++;
		if (*line == PIPE)
			return (*exit_status() = 1, FALSE);
	}
	return (TRUE);
}

int	line_verify(char *line)
{
	if (quoter(line) == FALSE)
		return (FALSE);
	if (redirection_check(line) == FALSE)
		return (FALSE);
	if (pipe_check(line) == FALSE)
		return (FALSE);
	if (standardizer(line) == FALSE)
		return (FALSE);
	return (TRUE);
}
