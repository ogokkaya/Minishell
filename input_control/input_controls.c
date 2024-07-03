/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:10:33 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/03 16:17:03 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_control(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == PIPE && line[i + 1] == PIPE)
            return (FALSE);
        i++;
    }
    return (TRUE);
}
static int quote_checker(char *line)
{
    int i;
    int single_quote;
    int double_quote;

    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (line[i])
    {
        if (line[i] == SINGLE_QUOTE)
            single_quote++;
        if (line[i] == DOUBLE_QUOTE)
            double_quote++;
        i++;
    }
    if (single_quote % 2 != 0 || double_quote % 2 != 0)
        return (FALSE);
    return (TRUE);
}

static int normalize_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
        {
            i++;
            while (line[i] != SINGLE_QUOTE && line[i] != DOUBLE_QUOTE)
                i++;
        }
        if (line[i] == PIPE)
            line[i] = SPACE;
        i++;
    }
    return (TRUE);
}

static int checker(char *line, int *i)
{
        if (line[*i] == PIPE)
            return (TRUE);
        if (line[*i] == SPACE)
        {
            while (line[*i] == SPACE)
                (*i)++;
            return (TRUE);
        }

    return (FALSE);
}
int line_arg_count(char *line)
{
    int count;
    int i;

    i = 0;
    count = 0;
    line = ft_strtrim(line, " ");
    if (quote_checker(line) == FALSE)
        return (ERR_RTN);
    while (line[i])
    {
        if (checker(line, &i) == TRUE)
            count++;
        i++;
    }
    count++;
    return (count);
}