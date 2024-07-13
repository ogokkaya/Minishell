/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:43:04 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/12 16:54:15 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env(t_env *env)
{
    if (!env)
        return (FALSE);
    while (env && env->name && env->content)
    {
        printf("%s=%s\n", env->name, env->content);
        env = env->next;
    }
    return (TRUE);

    //Burak bir şeyler dedi ama anlamadım tekrar sorucaz
    //"export a" yazıldığında "env" de görünmüyor ancak "export" yazıldığında görünüyor
    //"export a=" olmadığı sürece env de görünmüyor
}