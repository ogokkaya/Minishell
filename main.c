/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/01 18:14:23 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	t_mshell shell;

	// push TEST 1

	(void)av;
	shell.env = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Error\nBirden fazla girdi girilemez\n", 2),
			FALSE);
	if (get_env(env, &shell) == FALSE)
		return ((FALSE));
	/* 	while (shell.env != NULL)
		{
			printf("%s =", shell.env->name);
			printf("%s\n", shell.env->content);
			shell.env = shell.env->next;
		} */
	while (shell.env != NULL)
	{
		free(shell.env);
		shell.env = shell.env->next;
	}
	return (TRUE);
}