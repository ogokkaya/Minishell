/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/09 14:14:24 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>

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