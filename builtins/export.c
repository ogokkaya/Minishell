/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:15:19 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 17:59:45 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_env_exist(t_env *env, char *name)
{
    while (env)
    {
        if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0) //check for NAME and NAMEASD compare
            return (TRUE);
        env = env->next;
    }
    return (FALSE);
}

static int input_of_export(t_mshell *shell, t_command *command)
{
    int i;
    int j;
    int equal;
    char *name;
    char *content;
    t_env *env;

    env = NULL;
    i = 1;
    equal = 0;
    while (command->args[i])
    {
        
        j = 0;
        while (command->args[i][j++] )
            if (command->args[i][j] == '=')
            {
                equal = 1;
                break;
            }      
        if (id_validation(command->args[i]) == FALSE)
            return (FALSE);      
        name = fill_name(command, i, j, equal);
        content = fill_content(command, i, j, equal);
        if (ft_strncmp(shell->env->name, name, ft_strlen(name)) == 0)
            change_env(shell, name, content);
        else if (is_env_exist(shell->env, name) == FALSE)
            if_not_exist(shell, env, name, content);
        else if (equal == 1)
            change_env(shell, name, content);
        i++;
    }
    return (TRUE);
}

int export(t_mshell *shell)
{
    t_env *env;
    t_command *command;

    *exit_status() = 0;
    command = shell->command;
    if (!command->args[1])
    {
        env = shell->env;
        only_export(env);
    }
    else
        input_of_export(shell, command);
    return (TRUE);
}