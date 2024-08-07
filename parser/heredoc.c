/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:07:34 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:56:10 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	wait_process(t_command *command, int exit_value, int pid, int *fd)
{
	waitpid(pid, &exit_value, 0);
	*exit_status() = WEXITSTATUS(exit_value);
	if (*exit_status() != 0)
	{
		command->control = FALSE;
		close(fd[0]);
	}
	else
	{
		if (command->input != STDIN_FILENO)
			close(command->input);
		command->input = fd[0];
		command->heredoc = TRUE;
	}
}

void	heredoc_start(t_mshell *shell, char *delimiter, t_command *command)
{
	int		exit_value;
	pid_t	pid;
	int		fd[2];

	exit_value = 0;
	pipe_or_die(shell, fd);
	pid = fork_or_die(shell);
	g_signal_flag = SIGHEREDOC;
	if (pid == 0)
	{
		close(fd[0]);
		write_to_pipe(shell, delimiter, fd[1]);
		close(fd[1]);
		end_malloc(shell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		g_signal_flag = SIGSTRT;
		close(fd[1]);
		wait_process(command, exit_value, pid, fd);
	}
}

void	heredoc_start_before(t_mshell *shell, t_command *command,
		t_lexer *lexer)
{
	while (lexer != NULL && command != NULL)
	{
		if (lexer->type == TOKEN_HEREDOC && lexer->next != NULL)
		{
			if (lexer->next->type == TOKEN_WORD)
			{
				lexer = lexer->next;
				heredoc_start(shell, lexer->content, command);
			}
			else
				command->control = FALSE;
		}
		if (lexer->type == TOKEN_HEREDOC && lexer->next == NULL)
		{
			print_error2(1, NULL);
			command->control = FALSE;
		}
		if (lexer->type == TOKEN_PIPE)
			command = command->next;
		lexer = lexer->next;
	}
}
