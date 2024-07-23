/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:15:19 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/22 17:52:32 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_env_exist(t_env *env, char *name)
{
    while (env)
    {
        if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
            return (TRUE);
        env = env->next;
    }
    return (FALSE);
}

int input_of_export(t_mshell *shell, t_command *command)
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
            if (is_equal(command->args[i][j]) == TRUE)
            {
                equal = 1;
                break;
            }            
        name = ft_substr(command->args[i], 0, j);
        content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i]) - j);
         if (id_validation(name, content, equal) == FALSE)
            return (FALSE);
        if (ft_strncmp(shell->env->name, name, ft_strlen(name)) == 0)
          if_exist(env, content);
        else if (is_env_exist(shell->env, name) == FALSE)
            if_not_exist(shell, env, name, content);
        i++;
    }
    return (TRUE);
}

int export(t_mshell *shell)
{
    t_env *env;
    t_command *command;

    command = shell->command;
    
    if (!command->args[1])
    {
        env = shell->env;
        while (env && env->name && env->content)
        {
            if (ft_strncmp(env->name, "_", 1) != 0)
            {
                if (ft_strlen(env->content) > 0)
                    printf("declare -x %s=\"%s\"\n", env->name, env->content);
                else
                    printf("declare -x %s\n", env->name);
            }
            env = env->next;
        }
        return (TRUE);
    }
    else if (command->args[1])
    {
        input_of_export(shell, command);
    }
    return (TRUE);
}