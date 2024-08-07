/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:22:11 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 18:07:16 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>

void	print_error(char *cmd, int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	if (flag == 1)
	{
		ft_putstr_fd(NSFD, STDERR_FILENO);
		*exit_status() = 127;
	}
	if (flag == 2)
	{
		ft_putstr_fd(DRCTRY, STDERR_FILENO);
		*exit_status() = 126;
	}
	if (flag == 3)
	{
		ft_putstr_fd(PRMDNED, STDERR_FILENO);
		*exit_status() = 126;
	}
	if (flag == 5)
	{
		*exit_status() = 127;
		ft_putstr_fd(CNF, STDERR_FILENO);
	}
	if (flag == 6)
		ft_putstr_fd(NIVM, STDERR_FILENO);
}

void	print_error2(int flag, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (flag == 1)
	{
		ft_putstr_fd(SYSERROR, STDERR_FILENO);
		*exit_status() = 258;
	}
	if (flag == 2)
	{
		ft_putstr_fd(TMA, STDERR_FILENO);
		*exit_status() = 1;
	}
	if (flag == 3)
	{
		ft_putstr_fd("export : ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		*exit_status() = 1;
	}
}
