/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:22:49 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/02 13:50:46 by merboyac         ###   ########.fr       */
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

int	get_env(char **env, t_mshell *shell)
{
	char	**str;
	t_env	*new_env;

	/* if (shell->env)
		free(shell->env); */
	// bu kısım export ve unset için düşünülmüştü silinebilir
	while (*env)
	{
		str = ft_split(*env, '=');
		if (!str)
			return (FALSE);
		if (str[0] && str[1])
		{
			new_env = ft_lstnew_env(shell, ft_strdup(str[0]),
					ft_strdup(str[1]));
			if (!new_env)
				return (FALSE);
			ft_lstadd_back_env(&shell->env, new_env);
		}
		free_str(str);
		env++;
	}
	return (TRUE);
}

/* void	free_env(t_mshell *shell)
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
} */