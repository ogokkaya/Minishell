/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/23 02:49:09 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <./readline/history.h>
#include <./readline/readline.h>
#include <stdio.h>

int	shell_start_init(char **env, t_mshell *shell)
{
	shell->env = NULL;
	shell->lexer = NULL;
	shell->command = NULL;
	shell->block = malloc_starter();
	if (get_env(env, shell) == FALSE)
		return (printf(MALLOC), FALSE);
	return (TRUE);
}

int	shell_start(t_mshell *shell)
{
	shell->lexer = NULL;
	shell->command = NULL;
	shell->block = malloc_starter();
	return (TRUE);
}


void	read_line_cycle(t_mshell *shell)
{
	shell->input = readline(PROMT);
	if (!shell->input)
	{
		end_malloc(shell);
		// rl_clear_history();
		exit(1);
	}
	if (shell->input && !ft_isspace(shell->input))
	{
		add_history(shell->input);
		read_line_cycle(shell);
	}
	if (shell->input && line_verify(shell->input) == FALSE)
	{
		add_history(shell->input);
		printf("syntax error\n");
		read_line_cycle(shell);
	}
	// free(shell->input); leak gelmemesi için tekrarddda
	add_history(shell->input);
}

void	end_malloc_loop(t_mshell *shell)
{
	// rl_clear_history bu kısıma da eklenebilir
	ft_lstclear_memory(&shell->block, free);
}

// input olarak sadece '<<' girilirse syntax error vermeli
int	loop_shell(t_mshell *shell)
{
	t_mshell *shell_clone;

	shell_clone = shell;
	while (1)
	{
		read_line_cycle(shell);
		lexer(shell);
		parser(shell);
		execute(shell);
		end_malloc_loop(shell_clone);
		if (shell_start(shell) == FALSE)
			return (end_malloc(shell), FALSE);
	}
	return(TRUE);
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