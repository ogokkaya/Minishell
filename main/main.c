/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:48:27 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int			g_signal_flag = 0;

static int	shell_start_init(char **env, t_mshell *shell)
{
	g_signal_flag = SIGSTRT;
	shell->env = NULL;
	shell->lexer = NULL;
	shell->command = NULL;
	shell->shlvl = 1;
	shell->block = malloc_starter();
	if (get_env(env, shell) == FALSE)
		return (free_env(shell), printf(MALLOC), FALSE);
	if (!*env)
		mimic_bash(shell);
	return (TRUE);
}

static void	termios(void)
{
	struct termios	tmp;

	if (!tcgetattr(STDIN_FILENO, &tmp))
	{
		tmp.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mshell	shell;

	(void)av;
	termios();
	if (ac != 1)
		return (printf(ARG), FALSE);
	if (shell_start_init(env, &shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	signal_init();
	if (loop_shell(&shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	return (end_malloc(&shell), TRUE);
}
