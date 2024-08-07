/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:56:17 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 17:50:01 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>
#include <limits.h>
#include <unistd.h>

static int	shell_start(t_mshell *shell)
{
	shell->lexer = NULL;
	shell->command = NULL;
	shell->block = malloc_starter();
	return (TRUE);
}

static void	read_line_cycle(t_mshell *shell)
{
	shell->input = readline(PROMT);
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", 1);
		end_malloc(shell);
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	if (my_malloc(shell->block, shell->input))
		return (perror("read_loop"), end_malloc(shell), exit(EXIT_FAILURE));
	if (!ft_isspace(shell->input))
	{
		read_line_cycle(shell);
		return ;
	}
	if (line_verify(shell->input) == FALSE)
	{
		add_history(shell->input);
		print_error2(1, NULL);
		read_line_cycle(shell);
		return ;
	}
	add_history(shell->input);
}

static void	end_malloc_loop(t_mshell *shell)
{
	ft_lstclear_memory(&shell->block, free);
}

int	loop_shell(t_mshell *shell)
{
	t_mshell	*shell_clone;

	shell_clone = shell;
	while (1)
	{
		g_signal_flag = SIGPROMT;
		read_line_cycle(shell);
		lexer(shell);
		parser(shell);
		execute(shell);
		shell_clone = shell;
		end_malloc_loop(shell_clone);
		if (shell_start(shell) == FALSE)
			return (end_malloc(shell), FALSE);
	}
	return (TRUE);
}

void	mimic_bash(t_mshell *shell)
{
	char	path[PATH_MAX];
	char	*content;
	char	*shlvl;
	t_env	*env;

	env = NULL;
	shlvl = ft_itoa(shell->shlvl);
	if (my_malloc(shell->block, shlvl))
		return (end_malloc(shell), exit(EXIT_FAILURE));
	getcwd(path, PATH_MAX);
	content = ft_strdup(path);
	if (my_malloc(shell->block, content))
		return (end_malloc(shell), exit(EXIT_FAILURE));
	env = ft_lstnew_export_env("PWD", content);
	ft_lstadd_back_env(&shell->env, env);
	env = ft_lstnew_export_env("SHLVL", shlvl);
	ft_lstadd_back_env(&shell->env, env);
}
