/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/07 17:39:57 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


#include <stdio.h>

void parser(t_mshell *shell)
{
    t_lexer *ptr;

    ptr = shell->lexer;
    while (ptr != NULL)
    {
        ft_listadd_back_ast(&shell->ast, create_parser_node(shell, ptr));
        ptr = ptr->next;
    }

    while (shell->ast != NULL)
    {
        printf("content: %s\n", shell->ast->content->content);
        printf("type: %d\n", shell->ast->content->type);
        
        shell->ast = shell->ast->next;
    }
    
}
