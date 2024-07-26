/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:22 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 15:12:23 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "_" KONTROLÜ DE OLAN BİR SİLME KONTROLÜ YAPILACAK

#include "../minishell.h"

static int is_non_alpha(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isalpha(str[i]))
        {   
            printf("unset: `%s': not a valid identifier\n", str);
            return (*exit_status() = 1 ,1);
        }
        i++;
    }
    return (0);
}

static int validate_command(t_command *command, char *name)
{
    if (!command->args || !command->args[1])
        return (1);
    if (ft_strcmp(name, "_") == 0)
        return (*exit_status() = 1, 1);
    return (0);
}

static void free_envo(t_env *tmp, t_env *prev, t_env **env)
{
    if (prev)
        prev->next = tmp->next;
    else
        *env = tmp->next;
    free(tmp->name);
    free(tmp->content);
    free(tmp);
}

int unset(t_env *env, t_command *command)
{
    t_env *tmp;
    t_env *prev;
    char *name;
    int found = 0;
    int i = 1;
    
    if (validate_command(command, command->args[0]))
        return (1);
    tmp = env;
    prev = NULL;
    while (command->args[i])
    {
        name = command->args[i++];
        is_non_alpha(name);
        while (tmp)
        {
            if (ft_strcmp(tmp->name, name) == 0)
            {
                free_envo(tmp, prev, &env);
                found = 1;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return (found ? 0 : 1);
}
