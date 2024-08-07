/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:22 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 17:35:13 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static int	is_non_alpha(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (ft_isdigit(str[0]))
	{
		print_error(str, 6);
		return (*exit_status() = 1, 1);
	}
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
		{
			print_error(str, 6);
			return (*exit_status() = 1, 1);
		}
	}
	return (0);
}

static void	free_unset_env(t_env *tmp, t_env *prev, t_env **env)
{
	if (prev)
		prev->next = tmp->next;
	else
		*env = tmp->next;
	if (tmp->name)
		free(tmp->name);
	if (tmp->content)
		free(tmp->content);
	if (tmp)
		free(tmp);
}

void	unset(t_env **env, t_command *command)
{
	t_unset_vars	vars;

	vars.i = 0;
	while (command->args[vars.i])
	{
		if (is_non_alpha(command->args[(vars.i)++]))
			continue ;
		vars.tmp = *env;
		vars.prev = NULL;
		while (vars.tmp)
		{
			if (ft_strcmp(vars.tmp->name, command->args[vars.i - 1]) == 0)
			{
				vars.next = vars.tmp->next;
				free_unset_env(vars.tmp, vars.prev, env);
				vars.found = 1;
				vars.tmp = vars.next;
				break ;
			}
			vars.prev = vars.tmp;
			vars.tmp = vars.tmp->next;
		}
	}
}
