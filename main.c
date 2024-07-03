/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/03 16:15:18 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <./readline/history.h>
#include <./readline/readline.h>
#include <stdio.h>

int	shell_start_init(char **env, t_mshell *shell)
{
	shell->env = NULL;
	shell->block = malloc_starter();
	if (get_env(env, shell) == FALSE)
		return (printf(MALLOC), FALSE);
	return (TRUE);
}

void	read_line_cycle(t_mshell *shell)
{
	shell->input = readline(PROMT);
	if (!shell->input)
	{
		end_malloc(shell);
		rl_clear_history();
		exit(1);
	}
	if (shell->input && !ft_isspace(shell->input))
	{
		free(shell->input);
		read_line_cycle(shell);
	}
	// girdi kontrolü bu kısıma eklenecek
	//free(shell->input); leak gelmemesi için tekrarddda
	add_history(shell->input);
}

int	loop_shell(t_mshell *shell)
{
	while (1)
	{
		read_line_cycle(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mshell shell;

	(void)av;
	if (ac != 1)
		return (printf(ARG), FALSE);
	if (shell_start_init(env, &shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	if (loop_shell(&shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	return (TRUE);
}