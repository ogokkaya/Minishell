/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 13:19:31 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>

static int	flag_validator(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int flag_counter(t_command *command)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (command && command->args[j])
    {
        if (flag_validator(command->args[j]) == 1)
            i++;
        j++;
    }   
    return (i);
}
void echo_put(t_command *command)
{
    int flag_count;
    int i = 1;
    flag_count = flag_counter(command);
    if (flag_count != 0)
        i += flag_count;
    while (command->args[i])
    {
        ft_putstr_fd(command->args[i], 1);
        if (command->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (flag_count == 0)
        ft_putstr_fd("\n", 1);
}

int echo(t_command *command)
{
    *exit_status() = 0;
    echo_put(command);
    return (TRUE);
}
