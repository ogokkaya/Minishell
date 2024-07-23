/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:29:15 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/22 17:52:31 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void if_exist(t_env *env, char *content)
{
    free(env->content);
    env->content = content;
    if (env->content)
        printf("declare -x %s=\"%s\"\n", env->name, env->content);
}

void if_not_exist(t_mshell *shell, t_env *env, char *name, char *content)
{
    env = ft_lstnew_env(name, content);
    if (!env)
        return ;
    ft_lstadd_back_env(&shell->env, env);
}
int id_validation(char *name, char *content ,int equal)
{
    int i;

    i = 0;
        printf("%d\n", equal);
    if (ft_isalpha(name[i]) == 0 && name[i] != '_')
        return (printf("export: `%s': not a valid identifier\n",name),FALSE);
    i++;
    while (name[i])
    {
        if (ft_isalnum(name[i]) == 0 && name[i] != '_' && equal == 1)
            return (printf("export: `%s=%s': not a valid identifier\n", name, content),FALSE);
        else if (ft_isalnum(name[i]) == 0 && name[i] != '_' && equal == 0)
            return (printf("export: `%s': not a valid identifier\n", name),FALSE);
        i++;
    }
    return (TRUE);
}

int is_equal(char c)
{
    if (c == '=')
        return (TRUE);
    return (FALSE);
}
