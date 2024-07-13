/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/14 00:58:40 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// echo bdemirbu 

// echo "jvdfn" "frıfer" bu iki string arasında bir boşluk olmalı

static void count_arg_for_parser(t_lexer **lexer, int *redir_count, int *arg_count)
{
    while((*lexer)->next != NULL && (*lexer)->type != TOKEN_PIPE && (*lexer)->type != TOKEN_HEREDOC)
    {
        if((*lexer)->type == TOKEN_WORD)
            *arg_count += 1;
        if((*lexer)->type != TOKEN_WORD)
            *redir_count += 1;
        (*lexer) = (*lexer)->next;
    }
    // heredoc düşünülecek
    if((*lexer) && (*lexer)->type != TOKEN_PIPE && (*lexer)->type != TOKEN_HEREDOC)
    {
        if((*lexer)->type == TOKEN_WORD)
            *arg_count += 1;
        if((*lexer)->type != TOKEN_WORD)
            *redir_count += 1;
    }
}

void parsing_init(t_mshell *shell, t_lexer **lexer)
{
    t_command *command;
    int arg_count;
    int redir_count;

    redir_count = 0;
    arg_count = 0;
    count_arg_for_parser(&(*lexer), &redir_count, &arg_count);
    //printf("%d\n", arg_count);
    //printf("%d\n", redir_count);
    command = ft_calloc(1, sizeof(t_command));
    if(!command)
        return(perror("command"), end_malloc(shell), exit(1));
    my_malloc(shell->block, command);
    command->args = ft_calloc(arg_count + 1, sizeof(char *));
    if(!command->args)
        return(perror("command->args"), end_malloc(shell), exit(1));
    my_malloc(shell->block, command->args);
    command->redirection = ft_calloc(redir_count + 1, sizeof(t_redirection));
    if(!command->redirection)
        return(perror("command->redirection"), end_malloc(shell), exit(1));
    my_malloc(shell->block, command->redirection);
    ft_lstadd_parser(&shell->command , command);
}

void parser(t_mshell *shell)
{
    t_lexer *lexer;

    lexer = shell->lexer;
    while(lexer != NULL)
    {
        parsing_init(shell, &lexer);
        lexer = lexer->next;
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