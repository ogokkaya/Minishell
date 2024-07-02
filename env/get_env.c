/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:22:49 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/03 00:31:39 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_mshell *shell)
{
	t_env	*tmp;

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

static char *substr_from(const char *str, size_t start)
{
	size_t char_len;

	char_len = ft_strlen(str + start);
	return(ft_substr(str, start, char_len));
}

int get_env(char **env, t_mshell *shell)
{
	char *name;
	char *content;
	t_env *new_env;
	char *equel_value;
	size_t char_len;

	char_len = 0;
	while(*env)
	{
		equel_value = ft_strchr(*env, '=');
		if(!equel_value)
			return(FALSE);
		char_len = equel_value - *env;
		name = ft_substr(*env, 0, char_len);
		content = substr_from(*env, char_len + 1);
		if(!name || !content)
			return(FALSE);
		new_env = ft_lstnew_env(name, content);
		if(!new_env)
			return(FALSE);
		ft_lstadd_back_env(&shell->env, new_env);
		env++;
	}
	return(TRUE);
}
