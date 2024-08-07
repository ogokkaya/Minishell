/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:59 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:53:37 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "open_file.h"
#include <unistd.h>

static void	open_output_file(char *file_name, int flags, t_command *command)
{
	int	fd;

	if (flags == TOKEN_REDIR_OUT)
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, CREATE_MOD);
	else
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, CREATE_MOD);
	if (fd == -1)
	{
		check_path(file_name);
		*exit_status() = 1;
		command->control = FALSE;
	}
	if (command->output != STDOUT_FILENO)
		close(command->output);
	command->output = fd;
}

static void	open_input_file(char *file_name, t_command *command)
{
	int	fd;

	fd = open(file_name, O_RDONLY, CREATE_MOD);
	if (fd == -1)
	{
		file_check(file_name);
		command->control = FALSE;
		return ;
	}
	if (command->input != STDIN_FILENO && command->heredoc == TRUE)
	{
		close(fd);
		return ;
	}
	else if (command->input == STDIN_FILENO)
	{
		command->input = fd;
		return ;
	}
	else if (command->input != STDIN_FILENO)
	{
		close(command->input);
		command->input = fd;
		return ;
	}
}

void	file_creation(t_mshell *shell, t_command *command, t_lexer **lexer)
{
	if ((*lexer)->type == TOKEN_REDIR_APPEND && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		open_output_file((*lexer)->content, TOKEN_REDIR_APPEND, command);
	}
	else if ((*lexer)->type == TOKEN_REDIR_IN && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		unquote_the_output(shell, (*lexer));
		open_input_file((*lexer)->content, command);
	}
	else if ((*lexer)->type == TOKEN_REDIR_OUT && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		open_output_file((*lexer)->content, TOKEN_REDIR_OUT, command);
	}
}
