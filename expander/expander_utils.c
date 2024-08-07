/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:07:31 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 20:12:51 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

char	*ft_strchr_dollar(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] == '$')
			i++;
		else if (s[i] == '$' && s[i + 1] && !ft_isalnum_mshell(s[i + 1]) && s[i
				+ 1] != '?')
			i++;
		else if (s[i] == '$' && s[i + 1] != '$')
			break ;
		i++;
	}
	if (s[i] == '$' && s[i + 1] == '$')
		i++;
	if (s[i] == '$' && s[i + 1] == '\0')
		return (NULL);
	if (s[i] == '$' && s[i + 1] != '$')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*find_env(t_mshell *shell, char *path)
{
	t_env	*search_env;
	char	*content;

	search_env = shell->env;
	while (search_env != NULL)
	{
		if ((ft_strncmp(search_env->name, path,
					ft_strlen(search_env->name)) == 0)
			&& (ft_strncmp(search_env->name, path, ft_strlen(path)) == 0))
		{
			if (search_env->content)
				content = ft_strdup(search_env->content);
			else
				content = ft_strdup("");
			if (my_malloc(shell->block, content))
				return (perror("find_env"), end_malloc(shell), exit(1), NULL);
			return (content);
		}
		search_env = search_env->next;
	}
	content = ft_strdup("");
	if (my_malloc(shell->block, content))
		return (perror("find_env"), end_malloc(shell), exit(EXIT_FAILURE),
			NULL);
	return (content);
}

int	*exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

int	count_char(const char *str, char quote)
{
	int	quote_count;

	quote_count = 0;
	while (*str)
	{
		if (*str == quote)
		{
			quote_count++;
		}
		str++;
	}
	return (quote_count % 2);
}

t_quotes	quote_check(const char *str, size_t start)
{
	bool	in_single;
	bool	in_double;
	size_t	i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i] != '\0' && i < start)
	{
		if (str[i] == '\'' && in_double == false)
			in_single = !in_single;
		if (str[i] == '\"' && in_single == false)
			in_double = !in_double;
		i++;
	}
	if (in_double)
		return (IN_DOUBLE);
	else if (in_single)
		return (IN_SINGLE);
	return (NOT_QUOTED);
}
