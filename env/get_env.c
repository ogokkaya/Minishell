/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:22:49 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 19:50:13 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

void	free_env(t_mshell *shell)
{
	t_env	*tmp;

	if (shell->env)
		return ;
	while (shell->env != NULL)
	{
		if (shell->env->content)
			free(shell->env->content);
		free(shell->env->name);
		tmp = shell->env;
		shell->env = shell->env->next;
		free(tmp);
	}
}

static char	*substr_from(const char *str, size_t start)
{
	size_t	char_len;

	char_len = ft_strlen(str + start);
	return (ft_substr(str, start, char_len));
}

int	get_env(char **env, t_mshell *shell)
{
	t_get_env_vars	vars;

	while (env && *env)
	{
		vars.equal_value = ft_strchr(*env, '=');
		if (!vars.equal_value)
			return (FALSE);
		vars.char_len = vars.equal_value - *env;
		vars.name = ft_substr(*env, 0, vars.char_len);
		if (!vars.name)
			return (perror("get_env"), FALSE);
		vars.content = substr_from(*(env++), vars.char_len + 1);
		if (ft_strcmp(vars.name, "OLDPWD") == 0)
		{
			free(vars.content);
			vars.content = ft_strdup("");
		}
		if (!vars.content)
			return (perror("get_env"), free(vars.name), FALSE);
		vars.new_env = ft_lstnew_env(vars.name, vars.content);
		if (!vars.new_env)
			return (FALSE);
		ft_lstadd_back_env(&shell->env, vars.new_env);
	}
	return (TRUE);
}

void	change_env(t_mshell *shell, char *name, char *content)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->content);
			if (content)
			{
				tmp->content = ft_strdup(content);
				if (!tmp->content)
					return (perror("change_env"), end_malloc(shell),
						exit(EXIT_FAILURE));
			}
			else
				tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	add_export(t_mshell *shell, char *name, char *content)
{
	t_env	*new_env;

	new_env = ft_lstnew_export_env(name, content);
	ft_lstadd_back_env(&shell->env, new_env);
}
