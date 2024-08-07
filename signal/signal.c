/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:35:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:08:57 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <signal.h>

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_flag == SIGHEREDOC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			exit(1);
		}
		else if (g_signal_flag == SIGEXEC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		else if (g_signal_flag == SIGPROMT)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			*exit_status() = 1;
		}
	}
}

void	signal_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
