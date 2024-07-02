/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:16:40 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/02 13:22:11 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    error_exit(char *error_message, t_mshell *shell, int free_flag)
{
    ft_putstr_fd(error_message, 2);
    if (free_flag == TRUE)
        end_malloc(shell->block);
    exit(1);
}