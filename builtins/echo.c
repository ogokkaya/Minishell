/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:09 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/23 12:31:21 by merboyac         ###   ########.fr       */
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
int echo(t_mshell *shell)
{
    t_command *command;

    *exit_status() = 0;
    command = shell->command;
    echo_put(command);
    return (TRUE);
}

/* bash-3.2$ echo $asd_asdasd

bash-3.2$ ./minishell                           a bu duzelcek
minishell$ echo $asdasd_asdasd
_asdasd */