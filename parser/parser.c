/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/23 03:18:13 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>
#include "open_file.h"
#include <unistd.h>

static void	file_creation(t_mshell *shell, t_redirection *redirection,
		t_lexer **lexer)
{	
	if ((*lexer)->type == TOKEN_REDIR_APPEND && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		redirection->redir_fd = open_file((*lexer)->content, REDIR_APPEND);
	}
	else if ((*lexer)->type == TOKEN_REDIR_IN && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		redirection->redir_fd = open_file((*lexer)->content, REDIR_IN);
	}
	else if ((*lexer)->type == TOKEN_REDIR_OUT && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		redirection->redir_fd = open_file((*lexer)->content, REDIR_OUT);
	}
}

void	redirection(t_mshell *shell, t_command **command, t_lexer **lexer)
{
    if ((*lexer)->type == TOKEN_HEREDOC && (*lexer)->next != NULL)
    {
        (*lexer) = (*lexer)->next;
        heredoc_start(shell ,(*lexer)->content);
    }
    else
        file_creation(shell ,(*command)->redirection, &(*lexer));
    if((*command)->redirection->next)
		(*command)->redirection = (*command)->redirection->next;
}

void	parser_start(t_mshell *shell, t_command *command, t_lexer *lexer)
{
	int	index;

	index = 0;
	while (lexer != NULL && command != NULL)
	{
		if (lexer->type == TOKEN_WORD)
		{
			expander(shell, lexer);
			unquote_the_output(shell, lexer);
			command->args[index] = lexer->content;
			index++;
		}
		if (lexer->type == TOKEN_PIPE)
		{
			index = 0;
			pipe(command->pipe_fd);
			command = command->next;
		}
		if (lexer->type != TOKEN_WORD && lexer->type != TOKEN_PIPE)
			redirection(shell, &command, &lexer);
		lexer = lexer->next;
	}
	// pipe açılırken status düşünülecek
}

void	parser(t_mshell *shell)
{
	t_lexer	*lexer;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		parser_init(shell, &lexer);
		lexer = lexer->next;
	}
	save_restore_fd(STDIN_FILENO, STDOUT_FILENO, 0);
	parser_start(shell, shell->command, shell->lexer);
}
