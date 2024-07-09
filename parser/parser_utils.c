/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/09 15:20:20 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>

static char *remove_quotes_from_content(char *content, char quote)
{
    int i;
    int j;
    int content_len;
    char *new_content;

    i = -1;
    j = 0;
    content_len = ft_strlen(content);
    new_content = malloc(sizeof(char) * (content_len + 1));
    while(++i < content_len)
    {
        if(content[i] != quote)
        {
            new_content[j++] = content[i];
        }
    }
    if(new_content)
    {
        new_content[j] = '\0';
        return(new_content);
    }
    return(content);

}


void unquote_the_output(t_lexer *lexer)
{
    char *lexer_content_trim;

    while(lexer != NULL)
    {
        if(lexer->content[0] == '\'' && lexer->content[ft_strlen(lexer->content - 1) == '\''])
        {
            lexer_content_trim = remove_quotes_from_content(lexer->content, '\'');
            free(lexer->content);
            lexer->content = lexer_content_trim;
        }
        else
        {
            lexer_content_trim = remove_quotes_from_content(lexer->content, '\"');
            free(lexer->content);
            lexer->content = lexer_content_trim;
        }
        lexer = lexer->next;
    }
}

int ft_lst_parser(t_lexer *lexer)
{
    int i;

    i = 0;
    while (lexer)
    {
        if (lexer->type == TOKEN_WORD)
            i++;
        lexer = lexer->next;
    }
    return i;
}

t_ast *create_parser_node(t_lexer *lexer_ptr)
{
    t_ast *node;
    t_lexer *lexer;
    int i;

    i = ft_lst_parser(lexer_ptr);
    lexer = lexer_ptr;
    node = ft_calloc(1, sizeof(t_ast));
    if (!node)
        return NULL;
    node->content = ft_calloc(1, sizeof(t_content));
    if (!node->content)
        return NULL;
    node->content->content = ft_calloc(i + 1, sizeof(char *));
    if (!node->content->content)
        return NULL;
 
    return node;
}

void ft_listadd_back_ast(t_ast **lst, t_ast *new)
{
    t_ast *ptr;

    if (*lst == NULL)
        *lst = new;
    else
    {
        ptr = *lst;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = new;
        new->prev = ptr; // Listeyi çift yönlü bağlamak için prev alanını güncelle
    }
}