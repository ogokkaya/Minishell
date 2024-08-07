/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:29:38 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:43:36 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

static int	expand_dollar_env(t_mshell *shell, t_lexer *lexer,
		char *before_dollar, char *after_dollar)
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
		return (FALSE);
	expand = find_env(shell, var_name);
	dollar_changed = ft_strjoin(expand, &after_dollar[++index]);
	if (my_malloc(shell->block, dollar_changed))
		return (FALSE);
	lexer->content = ft_strjoin(before_dollar, dollar_changed);
	if (my_malloc(shell->block, lexer->content))
		return (perror("dollar_changed"), FALSE);
	return (TRUE);
}

static int	expand_exit_status(t_mshell *shell, t_lexer *lexer,
		char *before_dollar, char *after_dollar)
{
	char	*status;
	char	*after_dollar_changed;
	char	*changed_input;

	status = ft_itoa(*exit_status());
	if (my_malloc(shell->block, status))
		return (perror("exit_status"), FALSE);
	after_dollar_changed = ft_substr(after_dollar, 2, ft_strlen(after_dollar
				+ 2));
	if (my_malloc(shell->block, after_dollar_changed))
		return (perror("after_dollar_changed"), FALSE);
	changed_input = ft_strjoin(status, after_dollar_changed);
	if (my_malloc(shell->block, changed_input))
		return (perror("changed_input"), FALSE);
	lexer->content = ft_strjoin(before_dollar, changed_input);
	if (my_malloc(shell->block, lexer->content))
		return (perror("lexer->content"), FALSE);
	return (TRUE);
}

static int	dollar_expander(t_mshell *shell, t_lexer *lexer,
		char *before_dollar, char *after_dollar)
{
	if (after_dollar[0] == '$' && after_dollar[1] == '?')
	{
		if (expand_exit_status(shell, lexer, before_dollar,
				after_dollar) == FALSE)
			return (FALSE);
	}
	else if (after_dollar[0] == '$' && after_dollar[1])
	{
		if (after_dollar[0] == '$' && !ft_isalpha(after_dollar[1])
			&& (after_dollar[1] != '_'))
		{
			lexer->content = ft_strjoin(before_dollar, after_dollar + 2);
			if (my_malloc(shell->block, lexer->content))
				return (perror("dollar_changed"), FALSE);
			return (TRUE);
		}
		else if (expand_dollar_env(shell, lexer, before_dollar,
				after_dollar) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

static int	expand_tilde(t_mshell *shell, t_lexer *lexer)
{
	char	*home;
	char	*complete_home;

	home = find_env(shell, "HOME");
	if (lexer->content[0] == '~' && lexer->content[1] == '/')
	{
		complete_home = ft_strdup(lexer->content);
		if (my_malloc(shell->block, complete_home))
			return (perror("complete_home"), FALSE);
		lexer->content = ft_strjoin(home, complete_home + 1);
		if (my_malloc(shell->block, lexer->content))
			return (perror("~"), FALSE);
	}
	else if (lexer->content[0] == '~' && lexer->content[1] == '\0')
	{
		lexer->content = home;
	}
	return (TRUE);
}

void	expander(t_mshell *shell, t_lexer *lexer)
{
	char		*before_dollar;
	char		*after_dollar;
	t_quotes	quote_status;

	if (lexer->content[0] == '~')
		expand_tilde(shell, lexer);
	after_dollar = ft_strchr_dollar(lexer->content);
	while (after_dollar)
	{
		quote_status = quote_check(lexer->content, after_dollar
				- lexer->content);
		before_dollar = ft_substr(lexer->content, 0, after_dollar
				- lexer->content);
		if (my_malloc(shell->block, before_dollar))
			return (perror("exp_b_dol"), end_malloc(shell), exit(EXIT_FAILURE));
		if (quote_status != IN_SINGLE)
		{
			if (dollar_expander(shell, lexer, before_dollar,
					after_dollar) == FALSE)
				return (end_malloc(shell), exit(EXIT_FAILURE));
			after_dollar = ft_strchr_dollar(lexer->content);
		}
		else
			after_dollar = ft_strchr_dollar(after_dollar + 1);
	}
}
