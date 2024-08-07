/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:39:15 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:55:15 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>

static void	expan_heredoc_exit_status(t_mshell *shell, char **buffer,
		char *before_dollar, char *after_dollar)
{
	char	*status;
	char	*after_dollar_changed;
	char	*changed_input;

	status = ft_itoa(*exit_status());
	if (my_malloc(shell->block, status))
		return (perror("exit_status"), end_malloc(shell), exit(EXIT_FAILURE));
	after_dollar_changed = ft_substr(after_dollar, 2, ft_strlen(after_dollar
				+ 2));
	if (my_malloc(shell->block, after_dollar_changed))
		return (perror("after_dollar_changed"), end_malloc(shell),
			exit(EXIT_FAILURE));
	changed_input = ft_strjoin(status, after_dollar_changed);
	if (my_malloc(shell->block, changed_input))
		return (perror("changed_input"), end_malloc(shell), exit(EXIT_FAILURE));
	*buffer = ft_strjoin(before_dollar, changed_input);
	if (my_malloc(shell->block, *buffer))
		return (perror("lexer->content"), end_malloc(shell),
			exit(EXIT_FAILURE));
}

static void	expander_heredoc_env(t_mshell *shell, char **buffer,
		char *after_dollar, char *before_dollar)
{
	char	*var_name;
	char	*expand;
	char	*dollar_changed;
	int		index;

	index = 0;
	while (after_dollar[index++])
		if (!ft_isalnum_mshell(after_dollar[index]))
			break ;
	var_name = ft_substr(after_dollar, 1, --index);
	if (my_malloc(shell->block, var_name))
		return (perror("var_name"), end_malloc(shell), exit(EXIT_FAILURE));
	expand = find_env(shell, var_name);
	dollar_changed = ft_strjoin(expand, &after_dollar[++index]);
	if (my_malloc(shell->block, dollar_changed))
		return (perror("dollar_changed"), end_malloc(shell),
			exit(EXIT_FAILURE));
	*buffer = ft_strjoin(before_dollar, dollar_changed);
	if (my_malloc(shell->block, *buffer))
		return (perror("dollar_changed"), end_malloc(shell),
			exit(EXIT_FAILURE));
}

static void	expander_heredoc(t_mshell *shell, char **buffer)
{
	char	*after_dollar;
	char	*before_dollar;

	after_dollar = ft_strchr_dollar(*buffer);
	while (after_dollar)
	{
		if (after_dollar[0] == '$' && after_dollar[1] != '?'
			&& !ft_isalpha(after_dollar[1]) && (after_dollar[1] != '_'))
		{
			*buffer = ft_strjoin(before_dollar, after_dollar + 2);
			if (my_malloc(shell->block, *buffer))
				return (perror("dollar_changed"), end_malloc(shell),
					exit(EXIT_FAILURE));
			return ;
		}
		before_dollar = ft_substr(*buffer, 0, after_dollar - *buffer);
		if (my_malloc(shell->block, before_dollar))
			return (perror("ex_hrdc"), end_malloc(shell), exit(EXIT_FAILURE));
		if (after_dollar[0] == '$' && after_dollar[1] == '?')
			expan_heredoc_exit_status(shell, buffer, before_dollar,
				after_dollar);
		else
			expander_heredoc_env(shell, buffer, after_dollar, before_dollar);
		after_dollar = ft_strchr_dollar(*buffer);
	}
}

void	write_to_pipe(t_mshell *shell, char *delimeter, int writig_tip)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (my_malloc(shell->block, buffer))
			return (end_malloc(shell), exit(EXIT_FAILURE));
		if (!buffer || (ft_strcmp(buffer, delimeter) == 0))
			break ;
		if (!*buffer)
		{
			buffer = ft_strdup("\n");
			if (my_malloc(shell->block, buffer))
				return (end_malloc(shell), exit(EXIT_FAILURE));
		}
		else
			expander_heredoc(shell, &buffer);
		ft_putstr_fd(buffer, writig_tip);
		ft_putstr_fd("\n", writig_tip);
	}
}
