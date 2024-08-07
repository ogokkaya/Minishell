/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:15:19 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:45:10 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

static int	is_env_exist(t_env *env, char *name)
{
	while (env)
	{
		if ((ft_strlen(env->name) == ft_strlen(name)) && ft_strcmp(env->name,
				name) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

static int	control_equal(char c, int *i)
{
	if (c == '=')
	{
		*i = 1;
		return (1);
	}
	return (0);
}

static int	input_of_export(t_mshell *shell, t_command *command)
{
	t_export_vars	vars;

	vars = (t_export_vars){0};
	while (command->args[++vars.i])
	{
		vars.equal = 0;
		vars.j = 0;
		while (command->args[vars.i][vars.j++])
			if (control_equal(command->args[vars.i][vars.j], &vars.equal))
				break ;
		if (id_validation(command->args[vars.i]) == FALSE)
			continue ;
		vars.name = fill_name(command, vars.i, vars.j, vars.equal);
		vars.content = fill_content(command, vars.i, vars.j, vars.equal);
		if (!shell->env || is_env_exist(shell->env, vars.name) == FALSE)
			if_not_exist(shell, vars.name, vars.content);
		else if (!ft_strncmp(find_env(shell, vars.name), vars.name,
				ft_strlen(vars.name)) || (vars.equal == 1))
			change_env(shell, vars.name, vars.content);
		if (my_malloc(shell->block, vars.name))
			return (end_malloc(shell), exit(EXIT_FAILURE), FALSE);
		if (vars.content)
			my_malloc(shell->block, vars.content);
	}
	return (TRUE);
}

void	export(t_mshell *shell, t_command *command)
{
	t_env	*env;

	env = NULL;
	*exit_status() = 0;
	if (!command->args[1])
	{
		if (shell->env)
			env = shell->env;
		only_export(env, command);
	}
	else
		input_of_export(shell, command);
	return ;
}
