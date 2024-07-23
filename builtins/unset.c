/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:22 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/22 12:59:14 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "_" KONTROLÜ DE OLAN BİR SİLME KONTROLÜ YAPILACAK

#include "../minishell.h"

int check__unset(char *name)
{
    if (ft_strcmp(name, "_") == 0)
        return (1);
    return (0);
}
int unset(t_mshell *shell)
{
    t_env *tmp;
    t_env *prev;
    char *name;

    if (!shell->command->args || !shell->command->args[1])
        return (1);
    name = shell->command->args[1];
    if (check__unset(name) == 1)
        return (1);
    tmp = shell->env;
    prev = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            if (prev)
                prev->next = tmp->next;
            else
                shell->env = tmp->next;
            free(tmp->name);
            free(tmp->content);                 // ALOOOOOO BU FREELER NE OLMMMMM!
            free(tmp);
            free_malloc(shell->block, tmp);
            return (1);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (1);
}
//SİLME İŞLEMİ SIRASINDA ENVİRONMENT LİSTESİNDE OLAN BİR DEĞİŞKEN SİLİNİRSE SİLİNDİ MESAJI VERİLECEK
//BURADA ENV YAPISINDA OLAN BİR DEĞİŞKENSE DİREKT LİSTEDEKİ SIRASINDA GÜNCELLENEBİLİR