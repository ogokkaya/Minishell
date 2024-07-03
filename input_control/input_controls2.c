/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:05:30 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/03 20:00:30 by merboyac         ###   ########.fr       */
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