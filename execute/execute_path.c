/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:08:48 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 18:02:17 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*cmd_and_path(t_mshell *shell, char *cmd, char **path)
{
	char	*sub;
	char	*cmd_and_path;
	int		i;

	sub = ft_strjoin("/", cmd);
	if (my_malloc(shell->block, sub))
		return (perror("path"), end_malloc(shell), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (path[i])
	{
		cmd_and_path = ft_strjoin(path[i], sub);
		if (my_malloc(shell->block, cmd_and_path))
			return (perror("path"), end_malloc(shell), exit(EXIT_FAILURE),
				NULL);
		if ((path_exists(cmd_and_path) == TRUE)
			&& (is_directory(cmd_and_path) == TRUE))
		{
			if (can_execute(cmd_and_path) == TRUE)
				return (cmd_and_path);
			else
				return (print_error(cmd, 3), NULL);
		}
		i++;
	}
	return (print_error(cmd, 5), NULL);
}

char	*find_path(t_mshell *shell, t_command *command)
{
	char	*find_path;
	char	**path;
	char	*sub;
	char	**cmd1;
	int		i;

	cmd1 = command->args;
	if (cmd1[0] == (void *)0)
		return (NULL);
	if (*cmd1 && ft_strchr(*cmd1, '/'))
	{
		if (check_path(*cmd1) == TRUE)
			return (*cmd1);
		return (NULL);
	}
	sub = find_env(shell, "PATH");
	path = ft_split(sub, ':');
	if (my_malloc(shell->block, path))
		return (NULL);
	i = -1;
	while (path[++i])
		if (my_malloc(shell->block, path[i]))
			return (NULL);
	find_path = cmd_and_path(shell, *cmd1, path);
	return (find_path);
}
