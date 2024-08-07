/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:06:36 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

static int	flag_validator(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	else
		return (0);
	if (!str[i])
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == 0)
		return (1);
	else
		return (0);
}

static int	flag_counter(char **command)
{
	int	j;
	int	flag;

	j = 1;
	flag = 0;
	while (command[j])
	{
		while (command[j] && command[j][0] == 0)
			j++;
		if (flag_validator(command[j]) == 0)
			break ;
		else
			flag = 1;
		j++;
	}
	if (flag)
		return (j);
	return (1);
}

static void	echo_put(t_command *command)
{
	int	flag_count;
	int	i;

	i = 1;
	flag_count = flag_counter(command->args);
	if (flag_count > 1)
		i = flag_count;
	while (command->args[i])
	{
		if (command->args[i][0] != 0)
		{
			ft_putstr_fd(command->args[i], command->output);
			if (command->args[i + 1] && command->args[i][0] != 0)
				ft_putstr_fd(" ", command->output);
		}
		i++;
	}
	if (flag_count <= 1)
		ft_putstr_fd("\n", command->output);
}

void	echo(t_command *command)
{
	*exit_status() = 0;
	echo_put(command);
}
