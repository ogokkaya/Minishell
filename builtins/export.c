/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:15:19 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/21 18:03:11 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_of_export(t_mshell *shell, t_command *command)
{
    int i;
    int j;
    char *name;
    char *content;
    t_env *env;

    i = 1;
    while (command->args[i])
    {
        j = 0;
        while (command->args[i][j] && command->args[i][j] != '=')
            j++;
        name = ft_substr(command->args[i], 0, j);
        content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i]) - j);
        
        printf("name: %s\n", name);
        printf("content: %s\n", content);

        if (ft_strncmp(shell->env->name, name, ft_strlen(name)) == 0)
        {
            free(env->content);
            env->content = content;
            printf("declare -x %s=\"%s\"\n", env->name, env->content);
        }
        else
        {
            env = ft_lstnew_env(name, content);
            if (!env)
                return (FALSE);
            ft_lstadd_back_env(&shell->env, env);
        }
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
            printf("declare -x %s=\"%s\"\n", env->name, env->content);
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