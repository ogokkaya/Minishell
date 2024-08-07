/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:18:18 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:06:15 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

static int	_home(t_mshell *shell)
{
	char	*home;

	home = find_env(shell, "HOME");
	if (!home && ft_strcmp(home, "") == 0)
	{
		*exit_status() = 1;
		return (print_error(HMNTSET, 2), 1);
	}
	if (chdir(home) == -1)
		return (*exit_status() = 1, print_error(HMNTSET, 2), 1);
	return (0);
}

static int	find_env_cd(t_mshell *shell, char *path)
{
	t_env	*search_env;

	search_env = shell->env;
	while (search_env)
	{
		if (ft_strcmp(search_env->name, path) == 0)
			return (1);
		search_env = search_env->next;
	}
	return (0);
}

static int	update_pwd(t_mshell *shell, char *old_pwd)
{
	char	cwd[1024];
	char	*pwd;

	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
	{
		*exit_status() = 1;
		perror("getcwd");
		return (1);
	}
	if (find_env_cd(shell, "OLDPWD"))
		change_env(shell, "OLDPWD", old_pwd);
	else
		ft_lstadd_back_env(&shell->env, ft_lstnew_export_env("OLDPWD",
				old_pwd));
	if (find_env_cd(shell, "PWD"))
		change_env(shell, "PWD", pwd);
	else
		ft_lstadd_back_env(&shell->env, ft_lstnew_export_env("PWD", pwd));
	return (0);
}

void	cd(t_command *command, t_mshell *shell)
{
	char	*pwd;
	char	*path;
	char	*oldpwd;

	path = NULL;
	oldpwd = find_env(shell, "OLDPWD");
	*exit_status() = 0;
	if (!oldpwd)
		ft_lstadd_back_env(&shell->env, ft_lstnew_export_env("OLDPWD", ""));
	pwd = find_env(shell, "PWD");
	if (command->args[1])
		path = command->args[1];
	else if (_home(shell) == 0)
		path = find_env(shell, "HOME");
	else
		return ;
	if (chdir(path) == -1)
	{
		*exit_status() = 1;
		ft_putstr_fd("cd: " NSFD, 2);
		return ;
	}
	update_pwd(shell, pwd);
}
