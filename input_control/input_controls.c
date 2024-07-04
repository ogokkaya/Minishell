/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:10:33 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/04 14:10:20 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int quoter(char *line)
{
    static char quotes_flag;
    int quote_status;

    quote_status = 0;
    quotes_flag = '\0';
    while (*line != '\0')
    {
        if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
        {
            if (quote_status == 0)
            {
                quotes_flag = *line;
                quote_status = 1;
            }
            else if (quotes_flag == *line)
                quote_status = 0;
        }
        line++;
    }
    if (quote_status == 1)
        return (ft_putendl_fd("WRONG QUOTE USAGE (OR HEREDOC)", 2),FALSE);
    return (TRUE);
}

static int redirection_check(char *line)
{
    int redir_count = 0;

    while (*line)
    {
        if (*line == REDIRECT_OUT || *line == REDIRECT_IN)
        {
            redir_count++;
            if (redir_count >= 3)
            {
                return (ft_putendl_fd("WRONG REDIRECTION USAGE", 2), FALSE);
            }
        }
        else
        {
            redir_count = 0;
        }
        line++;
    }
    return (TRUE);
}

static int pipe_check(char *line)
{
    int pipe_count = 0;
    int in_command = 0;

    while (*line)
    {
        if (*line == PIPE)
        {
            if (pipe_count > 0 && !in_command)
                return (ft_putendl_fd("WRONG PIPE USAGE: Missing command between pipes", 2), FALSE);
            pipe_count++;
            in_command = 0;
            line++;
            while (*line && ft_space(*line))
                line++;
            if (*line == PIPE)
                return (ft_putendl_fd("WRONG PIPE USAGE: Consecutive pipes without command", 2), FALSE);
            continue;
        }
        else if (!ft_space(*line))
        {
            in_command = 1;
            pipe_count = 0;
        }
        line++;
    }
    if (pipe_count > 0 && !in_command)
        return (ft_putendl_fd("WRONG PIPE USAGE: Pipe at the end without command", 2), FALSE);
    return (TRUE);
}

static int standardizer(char *line)
{
    int i;

    i = ft_strlen(line);
        if (line[i] == SPACE)
        {
            while (line[i] == SPACE)
                i--;
            if (line[i] == PIPE)
                return (ft_putendl_fd("ENDLINE PIPE ERR", 2),FALSE);
        }

        if (*line == SPACE || *line == PIPE)
        {
            while (*line == SPACE)
                line++;
            if (*line == PIPE)
                return (ft_putendl_fd("FIRST CHAR PIPE ERR", 2), FALSE);
        }
    return (TRUE);
}

int line_verify(char *line)
{
    int i;

    i = 0;
    if (quoter(line) == FALSE)
        return (FALSE);
    if (redirection_check(line) == FALSE)
        return (FALSE);
    if (pipe_check(line) == FALSE)
        return (FALSE);
    if (standardizer(line) == FALSE)
        return (FALSE);
    return (TRUE);
}