/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/24 14:58:42 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
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

static int flag_counter(t_command *command)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (command && command->args[j++])
        if (flag_validator(command->args[j]) == 1)
            i++;
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

// builtin fonksiyonlara exit_status değerleri ayarlanıcak
int echo(t_command *command)
{
    *exit_status() = 0;
    echo_put(command);
    return (TRUE);
}