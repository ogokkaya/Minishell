/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:29:38 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/08 23:12:33 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// düzenlenicek olağan ve olağan dışı çıkışlar kontrol edilecek
static int expand_dollar_env(t_mshell *shell,t_lexer *lexer, char *before_dollar, char *after_dollar)
{
    char *var_name;
    char *expand;
    char *dollar_changed;
    int index;
    
    index = 0;
    if(after_dollar[0] == '$' && ft_strcmp(after_dollar, "$") != 0)
    {
        while(after_dollar[index++])
            if(!ft_isalnum(after_dollar[index]))
                break;
        var_name = ft_substr(after_dollar , 1, --index);
        expand = find_env(shell, var_name);
        dollar_changed = ft_strjoin(expand, &after_dollar[++index]);
        free(lexer->content);
        lexer->content = ft_strjoin(before_dollar, dollar_changed);
        free(var_name);
        free(expand);
        free(dollar_changed);
        if(!lexer->content)
            return(perror("dollar_changed"), FALSE);
    }
    return(TRUE);
}
static int expand_exit_status(t_lexer *lexer, char *before_dollar, char *after_dollar)
{
    char *status;
    char *after_dollar_changed;
    char *changed_input;

    status = ft_itoa(*exit_status());
    if(!status)
        return(perror("exit_status"), FALSE);
    after_dollar_changed = ft_substr(after_dollar, 2, ft_strlen(after_dollar + 2));
    changed_input = ft_strjoin(status, after_dollar_changed);
    free(status);
    free(after_dollar_changed);
    if(!changed_input)
        return(perror("changed_input"), FALSE);
    //my_malloc dan çıkarılacak ve oraya eklenecek
    free(lexer->content);
    lexer->content = ft_strjoin(before_dollar, changed_input);
    if(!lexer->content)
        return(perror("lexer->content"), FALSE);
    return(TRUE);
}

static int dollar_expander(t_mshell *shell,t_lexer *lexer, char *before_dollar, char *after_dollar)
{
    if(after_dollar[0] == '$' && after_dollar[1] == '?')
    {
        if(expand_exit_status(lexer ,before_dollar, after_dollar) == FALSE)
                return(FALSE);
    }
    else
    {
        if(expand_dollar_env(shell ,lexer, before_dollar, after_dollar) == FALSE)
            return(FALSE);
    }
    return(TRUE);
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
        complete_home = ft_strdup(lexer->content);
        if(!complete_home)
            return(perror("complete_home"), free(home), end_malloc(shell), exit(1));
        free(lexer->content),
        lexer->content = ft_strjoin(home, complete_home + 1);
        free(home);
        if(!lexer->content)
            return(perror("~"),free(complete_home), end_malloc(shell), exit(1));
        // block structından lexer ın bu adresi çıkartılacak yada direkt free(lexer->content)
    }
    else if(lexer->content[0] == '~' && lexer->content[1] == '\0')
    {
        // block structından lexer ın bu adresi çıkartılacak yada direkt free(lexer->content)
        lexer->content = home;
    }
    else
        free(home);
}

void expander(t_mshell *shell, t_lexer *lexer)
{
    char *before_dollar;
    char *after_dollar;

    while(lexer != NULL)
    {
        if(lexer->content[0] == '~')
            expand_tilde(shell, lexer);
        after_dollar = ft_strchr(lexer->content , '$');
        while(after_dollar)
        {
            before_dollar = ft_substr(lexer->content, 0, after_dollar - lexer->content);
            if(!before_dollar)
                return(perror("before_dollar"), end_malloc(shell), exit(1));
            else if(check_quotes(before_dollar, after_dollar))
            {
                if(dollar_expander(shell ,lexer, before_dollar, after_dollar) == FALSE)
                    return(free(before_dollar),end_malloc(shell), exit(1));
                after_dollar = ft_strchr(after_dollar + 1, '$');
            }
            else
                after_dollar = ft_strchr(after_dollar + 1, '$');
            free(before_dollar);
        }
        lexer = lexer->next;
    }
}
