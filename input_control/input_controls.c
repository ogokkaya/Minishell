/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:10:33 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/04 16:16:47 by merboyac         ###   ########.fr       */
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
    char last_redir = '\0';
    int in_quotes = 0;

    while (*line)
    {
        // Girdilerin tırnak içinde olup olmadığını kontrol eden if bloğu
        if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
        {
            if (in_quotes == 0)
                in_quotes = 1;
            else
                in_quotes = 0;
        }
        
        // Eğer tırnak içinde değilse ve girdi > veya < işaretlerinden biri ise devamında kullanımını kontrol eder
        if (!in_quotes && *line == REDIRECT_OUT || *line == REDIRECT_IN)
        {
            if (last_redir == REDIRECT_OUT && *line == REDIRECT_IN
                || last_redir == REDIRECT_IN && *line == REDIRECT_OUT)
                return (ft_putendl_fd("WRONG REDIRECTION USAGE: Consecutive opposite redirections", 2), FALSE);
            redir_count++;
            if (redir_count >= 3)
                return (ft_putendl_fd("WRONG REDIRECTION USAGE: Too many consecutive redirections", 2), FALSE);
            last_redir = *line;
        }
        else
        {
            redir_count = 0;
            last_redir = '\0';
        }
        line++;
    }
    return (TRUE);
}

static int pipe_check(char *line)
{
    int pipe_count = 0;
    int in_command = 0;
    int in_quotes = 0;

    while (*line)
    {
        // Girdilerin tırnak içinde olup olmadığını kontrol eden if bloğu
        if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
        {
            if (in_quotes == 0)
                in_quotes = 1;
            else
                in_quotes = 0;
        }
        // Eğer tırnak içinde değilse ve girdi | işareti ise devamında kullanımını kontrol eder
        if (!in_quotes && *line == PIPE)
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
    int in_quote;

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
    // tırnak kontrolü
    if (quoter(line) == FALSE)
        return (FALSE);
    // redirection kontrolü 
    if (redirection_check(line) == FALSE)
        return (FALSE);
    // pipe kontrolü
    if (pipe_check(line) == FALSE)
        return (FALSE);
    // 2. pipe kontrolü
    if (standardizer(line) == FALSE)
        return (FALSE);
    return (TRUE);
}