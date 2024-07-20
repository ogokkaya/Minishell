/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:18:18 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/20 17:48:18 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>


int _home(t_mshell *shell)
{
    char *home = find_env(shell, "HOME");
    if (!home)
        return (printf("cd: HOME not set\n"), 1);
    if (chdir(home) == -1)
        return (printf("cd: %s: No such file or directory\n", home), 1);
    return (0);
}


int cd(t_mshell *shell)
{
    char cwd[1024];
    char *pwd;
    char *oldpwd;
    char *path = NULL;

    pwd = find_env(shell, "PWD");
    oldpwd = find_env(shell, "OLDPWD");
    if (shell->lexer && shell->lexer->next && ft_strcmp(shell->lexer->content, "cd") == 0)
        path = shell->lexer->next->content;
    else if (_home(shell) == 0)
        path = find_env(shell, "HOME");
    if (!path || ft_strcmp(path, "") == 0)
        return (printf("cd: No path provided\n"), 1);
    else
        if (chdir(path) == -1)
            return (printf("cd: %s: No such file or directory\n", path), 1);
    change_env(shell, "OLDPWD", pwd);
    pwd = getcwd(cwd, sizeof(cwd));
    if (!pwd)
        return (perror("getcwd"), 1);
    change_env(shell, "PWD", cwd);
    return (0);
}
