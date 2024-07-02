/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:22:49 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/02 15:46:38 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_str(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}

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

int	get_env(char **env, t_mshell *shell)
{
	char	**str;
	t_env	*new_env;

	if (shell->env)
		free_env(shell);
	while (*env)
	{
		str = ft_split(*env, '=');
		if (!str)
			return (FALSE);
		if (str[0] && str[1])
		{
			new_env = ft_lstnew_env(ft_strdup(str[0]), ft_strdup(str[1]));
			if (!new_env)
				return (FALSE);
			ft_lstadd_back_env(&shell->env, new_env);
		}
		free_str(str);
		env++;
	}
	return (TRUE);
}
