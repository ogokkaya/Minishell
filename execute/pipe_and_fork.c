/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:01:42 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:42:18 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	pipe_or_die(t_mshell *shell, int *fd)
{
	if (pipe(fd) == -1)
	{
		print_err_pipe_and_fork(TOKEN_PIPE);
		end_malloc(shell);
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_or_die(t_mshell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_err_pipe_and_fork(TOKEN_FORK);
		end_malloc(shell);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
