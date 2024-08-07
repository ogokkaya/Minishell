/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:43:04 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 17:28:14 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	env_controller(t_command *command)
{
	if (command->args[1])
	{
		*exit_status() = 127;
		printf("env: %s: No such file or directory\n", command->args[1]);
		return (0);
	}
	return (1);
}

void	env(t_env *env, t_command *command)
{
	*exit_status() = 0;
	if (!env)
		return ;
	if (!env_controller(command))
		return ;
	while (env && env->name)
	{
		if (env->name && env->content == NULL)
			env = env->next;
		else if (env->name && env->content)
		{
			ft_putstr_fd(env->name, command->output);
			ft_putstr_fd("=", command->output);
			ft_putendl_fd(env->content, command->output);
			env = env->next;
		}
		else
			env = env->next;
	}
	return ;
}
