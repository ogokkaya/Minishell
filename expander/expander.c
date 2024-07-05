/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:29:38 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/05 14:24:00 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char *find_env(t_mshell *shell, char *path)
{
    t_env *search_env;

    search_env = shell->env;
    while(search_env != NULL)
    {
        if(ft_strcmp(search_env->name, path) == 0)
            return(ft_strdup(search_env->content));
        search_env = search_env->next;
    }
    return(ft_strdup(""));
    // bu kısım düşünülmeli
}


void expand_tilde(t_mshell *shell, t_lexer *lexer)
{
    char *home;
    char *complete_home;

    home = find_env(shell, "HOME");
    if(!home)
        return(perror("home"), end_malloc(shell), exit(1));
    if(lexer->content[0] == '~' && lexer->content[1] == '/')
    {
        complete_home = ft_strjoin(home, "/");
        if(!complete_home)
            return(perror("complete_home"), free(home), end_malloc(shell), exit(1));
        free(home);
        // block structından lexer ın bu adresi çıkartılacak yada direkt free(lexer->content)
        lexer->content = complete_home;
        
    }
    else if(lexer->content[0] == '~' && lexer->content[1] == '\0')
    {
        // block structından lexer ın bu adresi çıkartılacak yada direkt free(lexer->content)
        lexer->content = home;
    }
    else
        free(home);
}

void expender(t_mshell *shell)
{
    //char *extended_input;
    char *temporary;
    t_lexer *lexer;

    lexer = shell->lexer;
    while(lexer != NULL)
    {
        if(lexer->content[0] == '~')
            expand_tilde(shell, lexer);
        temporary = ft_strchr(lexer->content , '$');
        while(temporary)
        {
            
        }  
        lexer = lexer->next;
    }       
}