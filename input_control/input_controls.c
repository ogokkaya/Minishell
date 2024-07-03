/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:10:33 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/03 20:16:53 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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

static int standardizer(char *line)
{
    *line++;
    return (TRUE);
}

int line_verify(char *line)
{
    int i;

    i = 0;
    if (quoter(line) == FALSE)
        return (FALSE);
    if (standardizer(&line) == FALSE)
        return (FALSE);

    printf("line: %s\n", line);
    return (TRUE);
}