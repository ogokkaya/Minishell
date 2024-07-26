/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:29:15 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 17:18:04 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* t_env   *tmp_start_env(void)
{
    t_env *env;

    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->name = NULL;
    env->content = NULL;
    env->next = NULL;
    return (env);
} */

void if_not_exist(t_mshell *shell, t_env *env, char *name, char *content)
{
    env = ft_lstnew_env(name, content);
    if (!env)
        return ;
    ft_lstadd_back_env(&shell->env, env);
}

int id_validation(char *command)
{
    int i;

    i = 0;
    if (ft_isalpha(command[i]) == 0 && command[i] != '_')
        return (printf("export: `%s': not a valid identifier\n",command),
            *exit_status() = 1, FALSE);
    i++;
    while (command[i] && command[i] != '=')
    {
        if (ft_isalnum(command[i]) == 0 && command[i] != '_' && command[i] != '=')
        {
                printf("export: `%s': not a valid identifier\n", command);
            return (*exit_status() = 127 ,FALSE);
        }
        i++;
    }
    return (TRUE);
}
