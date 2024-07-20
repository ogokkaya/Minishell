/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/20 16:58:19 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <./readline/history.h>
#include <./readline/readline.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// echo "jvdfn" "frıfer" bu iki string arasında bir boşluk olmalı

static void	file_creation(t_mshell *shell, t_redirection *redirection,
		t_lexer **lexer)
{
	if ((*lexer)->type == TOKEN_REDIR_APPEND && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		redirection->redir_fd = open((*lexer)->content,
				O_CREAT | O_RDWR | O_APPEND, 0777);
		if (redirection->redir_fd == -1)
			return (perror((*lexer)->content));
	}
	else if ((*lexer)->type == TOKEN_REDIR_IN && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		redirection->redir_fd = open((*lexer)->content, O_CREAT, 0777);
		if (redirection->redir_fd == -1)
			return (perror((*lexer)->content));
	}
	else if ((*lexer)->type == TOKEN_REDIR_OUT && (*lexer)->next != NULL)
	{
		(*lexer) = (*lexer)->next;
		expander(shell, (*lexer));
		unquote_the_output(shell, (*lexer));
		redirection->redir_fd = open((*lexer)->content,
				O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (redirection->redir_fd == -1)
			return (perror((*lexer)->content));
	}
}

void	redirection(t_mshell *shell, t_command **command, t_lexer **lexer)
{
	int	index;

    index = 0;
    if ((*lexer)->type == TOKEN_HEREDOC && (*lexer)->next != NULL)
    {
        (*lexer) = (*lexer)->next;
        heredoc_start(shell ,&(*command)->redirection[index],(*lexer)->content);
    }
    else
        file_creation(shell ,&(*command)->redirection[index], &(*lexer));
    if(&(*command)->redirection[index + 1])
        index++;
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
	parser_start(shell, shell->command, shell->lexer);
}
