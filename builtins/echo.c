/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/20 13:20:23 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static int flag_validator(char *flag)
{
    if (!flag)
        return (0);
    if (flag[0] != '-')
        return (0);
    if (!flag[0])
        return (0);
    if (flag[1] != 'n')
        return (0);
    return (1);
}

static int flag_counter(t_lexer *lexer)
{
    int i = 0;

    while (lexer && lexer->content && lexer->next)
    {
        if (flag_validator(lexer->content) == 1)
            i++;
        lexer = lexer->next;
    }
    return (i);
}
void echo_put(t_lexer *lexer, int fd)
{
    int flag_count;
    int i = 0;
    flag_count = flag_counter(lexer);
    lexer = lexer->next;
    while (i++ < flag_count)
        lexer = lexer->next;
    while (lexer)
    {
        ft_putstr_fd(lexer->content, fd);
        if (lexer->next && lexer->next->content && lexer->next->type == TOKEN_WORD)
            ft_putstr_fd(" ", fd);
        lexer = lexer->next;
    }
    if (flag_count == 0)
        ft_putstr_fd("\n", fd);
}

int echo(t_mshell *lexer)
{
    echo_put(lexer->lexer, 1);
    return (TRUE);
}