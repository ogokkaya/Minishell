/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:43:04 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/22 13:32:21 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env_controller(t_command *command)
{
    if (command->args[1])
    {
        printf("env: %s: No such file or directory\n", command->args[1]);
        return (0);
    }
    return (1);
}

int env(t_env *env, t_command *command)
{
    if (!env)
        return (FALSE);
    if (!env_controller(command))
        return (FALSE);
    while (env && env->name && env->content)
    {
        if (ft_strlen(env->content) != 0)
            printf("%s=%s\n", env->name, env->content);
        env = env->next;
    }
    return (TRUE);
}