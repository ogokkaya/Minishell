/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 17:58:25 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

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
			command = command->next;
		}
		if (lexer->type != TOKEN_WORD && lexer->type != TOKEN_PIPE
			&& lexer->next)
			lexer = lexer->next;
		lexer = lexer->next;
	}
}

void	parser(t_mshell *shell)
{
	t_lexer		*lexer;
	t_command	*command;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		parser_init(shell, &lexer);
		lexer = lexer->next;
	}
	parser_start(shell, shell->command, shell->lexer);
	command = shell->command;
	while (command)
	{
		while (*command->args && command->args[0][0] == 0)
			command->args = &command->args[1];
		command = command->next;
	}
	heredoc_start_before(shell, shell->command, shell->lexer);
}
