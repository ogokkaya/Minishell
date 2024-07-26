/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:54:53 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 13:27:40 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int pwd()
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != 0)
        return (printf("%s\n", cwd), *exit_status() = 0, TRUE);
    else
        return (perror("cwd err") ,*exit_status() = 1, FALSE);
}