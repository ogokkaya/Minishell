/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/07 17:35:41 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast *create_parser_node(t_mshell *shell, t_lexer *lexer)
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
}