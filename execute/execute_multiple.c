/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:08:09 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:37:50 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	child_control(t_mshell *shell)
{
	int			child_status;
	t_command	*command;

	child_status = 0;
	command = shell->command;
	while (command->next)
		command = command->next;
	if (command->child_pid != 0)
	{
		waitpid(command->child_pid, &child_status, 0);
		if (WIFEXITED(child_status))
			*exit_status() = WEXITSTATUS(child_status);
		else if (WIFSIGNALED(child_status))
			*exit_status() = 128 + (WTERMSIG(child_status));
	}
	while (wait(NULL) != -1)
		;
}

static void	multiple_exec_start(t_mshell *shell, t_command *command)
{
	char	**env;
	char	*path;

	path = find_path(shell, command);
	if (!path || command->control == FALSE)
		return (end_malloc(shell), exit(EXIT_FAILURE));
	env = execute_env(shell);
	duplicate(command);
	execve(path, command->args, env);
	end_malloc(shell);
	exit(EXIT_FAILURE);
}

void	multiple_execute(t_mshell *shell, t_command *command, t_lexer *lexer)
{
	int	pid;

	pid = -2;
	while (lexer && lexer->type != TOKEN_PIPE)
	{
		if (command->control == TRUE)
			file_creation(shell, command, &lexer);
		lexer = lexer->next;
	}
	if (lexer && lexer->next && lexer->type == TOKEN_PIPE)
		shell->lexer = lexer->next;
	pid = fork_or_die(shell);
	if (pid == 0)
	{
		if (builtin_control(command, command->args[0]) == TRUE)
		{
			if (command->control == FALSE)
				return (end_malloc(shell), exit(*exit_status()));
			return (builtin_start(shell, command, 1), exit(*exit_status()));
		}
		else
			multiple_exec_start(shell, command);
	}
	else
		command->child_pid = pid;
}
