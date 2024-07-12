/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/11 16:13:59 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static int flag_validator(char *flag)
{
    int i;

    i = 0;
    if (!flag)
        return (0);
    while (flag[i] != '-' && flag[i] != '\0')
        i++;
    if (flag[i] == '-')
        i++;
    if (!flag[i])
        return (0);
    while (flag[i])
    {
        if (flag[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

static int flag_counter(char *flags)
{
    int i;
    int count;
    
    i = 0;
    while (flags[i] && flags)
    {
        if (flag_validator(flags) == 0)
            break;
        i++;
    }
    return (i);
}
void echo_put(t_lexer *lexer, int fd)
{
    int i;
    int flag_count;
    char *flags;

    flags  = lexer->content;
    if (flag_counter(flags) != 0)
        lexer = lexer->next;
    flag_count = flag_counter(flags);
    while (lexer)
    {
        ft_putstr_fd(lexer->content, fd);
        if(lexer->next && lexer->next->content && lexer->next->type == TOKEN_WORD)
            ft_putstr_fd(" ", fd);
        lexer = lexer->next;
    }
    if (flag_count == 0)
        ft_putstr_fd("\n", fd);
}

int echo(t_lexer *lexer)
{
    echo_put(lexer, 1);
    return (TRUE);
}

int main()
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->content = "echoaoekpfaeo";
    lexer->type = TOKEN_WORD;
    lexer->next = malloc(sizeof(t_lexer));
    lexer->next->content = "kaofea";
    lexer->next->type = TOKEN_WORD;
    lexer->next->next = malloc(sizeof(t_lexer));
    lexer->next->next->content = "-n";
    lexer->next->next->type = TOKEN_WORD;
    lexer->next->next->next = malloc(sizeof(t_lexer));
    lexer->next->next->next->content = "world";
    lexer->next->next->next->type = TOKEN_WORD;
    lexer->next->next->next->next = NULL;

    lexer = lexer->next;
    echo(lexer);    
    return (0);
}