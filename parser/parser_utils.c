/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/23 03:11:27 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "open_file.h"
#include <unistd.h>
#include <stdio.h>

static char	*remove_quotes_from_content(t_mshell *shell,char *content, char double_quote,
		char single_quote)
{
	int		i;
	int		j;
	int		content_len;
	char	*new_content;

	i = 0;
	j = 0;
	content_len = ft_strlen(content);
	new_content = malloc(sizeof(char) * (content_len + 1));
	if (!new_content)
		return (perror("new_content"), end_malloc(shell), exit(1), NULL);
	while (i < content_len)
	{
		if (content[i] == double_quote && !(count_char(&content[i], double_quote)))
				while (content[++i] != double_quote && i < content_len)
					new_content[j++] = content[i];
		else if (content[i] == single_quote && !(count_char(&content[i], single_quote)))
			while (content[++i] != single_quote && i < content_len)
				new_content[j++] = content[i];
		else if(content[i] != double_quote && content[i] != single_quote)
			new_content[j++] = content[i++];
		else
			i++;
	}
	return ((new_content[j] = '\0'),new_content);
}

int open_file(char *file_name, int flags)
{
	int fd;
	int dup_fd;

	fd = open(file_name, flags, 0777);
	if(fd == -1)
		return(perror_write(file_name, NSFD), 0);
	if(flags == REDIR_IN)
		dup_fd = dup2(fd , STDIN_FILENO);
	else
		dup_fd = dup2(fd , STDOUT_FILENO);
	close(fd);
	if(dup_fd == -1)
		perror(file_name);
	return(fd);
}


void	unquote_the_output(t_mshell *shell,t_lexer *lexer)
{
	char	*lexer_content_trim;

	lexer_content_trim = remove_quotes_from_content(shell,lexer->content, '\"', '\'');
	lexer->content = lexer_content_trim;
}
static void	ft_lstadd_parser(t_command **lst, t_command *new)
{
	t_command	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	new->next = NULL;
}

static void	ft_lstadd_redirection(t_redirection **lst, t_redirection *new)
{
	t_redirection	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
		new->r_stdin = STDIN_FILENO;
		new->r_stdout = STDOUT_FILENO;
		new->prev = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->r_stdin = STDIN_FILENO;
		new->r_stdout = STDOUT_FILENO;
		new->prev = ptr;
	}
	new->next = NULL;
}

static void	count_arg_for_parser(t_lexer **lexer, int *redir_count,
		int *arg_count)
{
	while ((*lexer)->next != NULL && (*lexer)->type != TOKEN_PIPE)
	{
		if ((*lexer)->type == TOKEN_WORD)
			*arg_count += 1;
		if ((*lexer)->type != TOKEN_WORD)
			*redir_count += 1;
		(*lexer) = (*lexer)->next;
	}
	// heredoc düşünülecek
	if ((*lexer) && (*lexer)->type != TOKEN_PIPE)
	{
		if ((*lexer)->type == TOKEN_WORD)
			*arg_count += 1;
		if ((*lexer)->type != TOKEN_WORD)
			*redir_count += 1;
	}
}

void	parser_init(t_mshell *shell, t_lexer **lexer)
{
	t_command	*command;
	int			arg_count;
	int			redir_count;

	redir_count = 0;
	arg_count = 0;
	count_arg_for_parser(&(*lexer), &redir_count, &arg_count);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (perror("command"), end_malloc(shell), exit(1));
	my_malloc(shell->block, command);
	command->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!command->args)
		return (perror("command->args"), end_malloc(shell), exit(1));
	my_malloc(shell->block, command->args);
	command->redirection = ft_calloc(redir_count + 1, sizeof(t_redirection));
	if (!command->redirection)
		return (perror("command->redirection"), end_malloc(shell), exit(1));
	my_malloc(shell->block, command->redirection);
	ft_lstadd_parser(&shell->command, command);
	ft_lstadd_redirection(&shell->command->redirection, command->redirection);
}
