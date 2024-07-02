/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:16:40 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/03 00:40:36 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *error_message, t_mshell *shell, int free_flag)
{
	ft_putstr_fd(error_message, 2);
	if (free_flag == TRUE)
		end_malloc(shell);
	exit(1);
}