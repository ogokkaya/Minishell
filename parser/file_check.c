/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:48:40 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:54:07 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <unistd.h>

static void	print_error_file(char *cmd, int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	if (flag == 1)
	{
		ft_putstr_fd(NSFD, STDERR_FILENO);
		*exit_status() = 1;
	}
	if (flag == 2)
	{
		ft_putstr_fd(DRCTRY, STDERR_FILENO);
		*exit_status() = 1;
	}
	if (flag == 3)
	{
		ft_putstr_fd(PRMDNED, STDERR_FILENO);
		*exit_status() = 1;
	}
}

int	file_check(char *path)
{
	if (path_exists(path) == FALSE)
	{
		print_error_file(path, 1);
		return (FALSE);
	}
	if (is_directory(path) == FALSE)
	{
		print_error_file(path, 2);
		return (FALSE);
	}
	if (can_execute(path) == FALSE)
	{
		print_error_file(path, 3);
		return (FALSE);
	}
	return (TRUE);
}
