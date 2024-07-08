/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/08 23:09:55 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


/* t_ast *create_parser_node(t_mshell *shell, t_lexer *lexer)
{
    t_ast *node;

    node = ft_calloc(1, sizeof(t_ast));
    if (!node)
        return NULL;
    node->content = ft_calloc(1, sizeof(t_content)); // t_content için bellek ayırma
    if (!node->content) {
        free(node); // Bellek sızıntısını önlemek için node'u serbest bırak
        return NULL;
    }
    node->content->type = lexer->type;
    node->content->content = lexer->content;
    node->next = NULL;
    node->prev = NULL;
    my_malloc(shell->block, node);
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

int pipe_count(t_mshell *shell)
{
    t_lexer *ptr;
    int count;

    ptr = shell->lexer;
    count = 0;
    while (ptr != NULL)
    {
        if (ptr->type == TOKEN_PIPE)
            count++;
        ptr = ptr->next;
    }
    return (count);
} */