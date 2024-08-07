/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:06:30 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 19:20:32 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	skip_ws(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static void	exit_with_err(t_mshell *shell, t_command *command)
{
	ft_putstr_fd("exit\n", command->output);
	ft_putstr_fd("minishell: exit: ", command->output);
	ft_putstr_fd(shell->command->args[1], command->output);
	ft_putstr_fd(": numeric argument required\n", command->output);
	end_malloc(shell);
	exit(255);
}

static void	set_flag_exit(t_mshell *shell, t_command *command)
{
	int		rtn;
	char	*str_trim;
	int		i;

	i = 0;
	str_trim = ft_strtrim(command->args[1], "\t\n\r\f\v ");
	if (my_malloc(shell->block, str_trim))
		return (end_malloc(shell), perror("str_trim"), exit(EXIT_FAILURE));
	command->args[1] = str_trim;
	while (skip_ws(command->args[1][i]))
		i++;
	if (command->args[1][i] == '-' || command->args[1][i] == '+')
		i++;
	while (command->args[1][i])
	{
		if (!ft_isdigit(command->args[1][i]))
			exit_with_err(shell, command);
		i++;
	}
	rtn = ft_atoi(command->args[1]);
	ft_putstr_fd("exit\n", command->output);
	end_malloc(shell);
	*exit_status() = (256 + rtn) % 256;
	exit(*exit_status());
}

int	get_cmd_count(t_command *command)
{
	int	count;
	int	i;

	i = 0;
	count = -1;
	while (command && command->args[i])
	{
		count++;
		i++;
	}
	return (count);
}

void	ft_exit(t_mshell *shell, t_command *command)
{
	int	cmd_count;

	if (ft_strlen(command->args[1]) > 19)
		(exit_with_err(shell, command));
	cmd_count = get_cmd_count(command);
	if (cmd_count == 0)
	{
		ft_putstr_fd("exit\n", command->output);
		*exit_status() = 0;
		end_malloc(shell);
		exit(0);
	}
	if (cmd_count > 1 && arg_order(command->args[1]))
	{
		ft_putstr_fd("exit\n", command->output);
		print_error2(2, NULL);
		return ;
	}
	else if (command->args && command->args[1])
		set_flag_exit(shell, command);
}
