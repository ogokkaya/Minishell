/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:18:18 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/25 15:08:51 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>


int _home(t_mshell *shell)
{
    char    *home;
    
    home = find_env(shell, "HOME");
    if (ft_strcmp(home, "") == 0)
        return (*exit_status() = 1, printf("cd: HOME not set\n"), 1);
    if (chdir(home) == -1)
        return (*exit_status() = 1,
                 printf("cd: %s: No such file or directory\n", home), 1);
    return (0);
}


int cd(t_command *command, t_mshell *shell)
{
    char cwd[1024];
    char *pwd;
    char *path = NULL;

    *exit_status() = 0;
    pwd = find_env(shell, "PWD");
    if (command->args[1])
        path = command->args[1];
    else if (_home(shell) == 0)
        path = find_env(shell, "HOME");
    else
        return (1);
    if (chdir(path) == -1 && ft_strcmp(path, "") != 0)
       return (*exit_status() = 1,
        printf("cd: %s: No such file or directory\n", path), 1);
    else
        chdir(path);
    change_env(shell, "OLDPWD", pwd);
    pwd = getcwd(cwd, sizeof(cwd));
    if (!pwd)
        return (*exit_status() = 1, perror("getcwd"), 1);
    change_env(shell, "PWD", cwd);
    return (0);
}
