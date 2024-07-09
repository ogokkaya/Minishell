/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/09 15:21:45 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


#include <stdio.h>

void parse_command_and_args(t_ast *ast, t_lexer **current_token, t_mshell *shell) 
{    
    t_ast *new_node;
    int i = 0;

    (void)shell;
    (void)ast;
    new_node = create_parser_node(*current_token);
    if (!new_node)
        exit(1); //RETURN ERROR
    new_node->content->type = (*current_token)->type;
    new_node->content->content[i] = ft_strdup((*current_token)->content);
    (*current_token) = (*current_token)->next;
    while ((*current_token) && (*current_token)->type == TOKEN_WORD)
    {
        new_node->content->content[++i] = ft_strdup((*current_token)->content);
        (*current_token) = (*current_token)->next;
        printf("content: %s\n", new_node->content->content[i]);
    }
}
// echo bdemirbu 

void parser(t_mshell *shell)
{
    t_lexer *current_token;
    t_ast *ast;

    unquote_the_output(shell->lexer);
    current_token = shell->lexer;
    ast = NULL;
    while (current_token)
    {
        if (current_token->type == TOKEN_WORD)
            parse_command_and_args(ast, &current_token, shell);
    }
}

// echo asd eqw >> test.txt | cat -l

// echo
// asd
// eqw
// >>
// test.txt
// |
// cat
// -l