/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/01 20:41:18 by ogokkaya         ###   ########.fr       */
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
	shell.block = malloc_starter();
	if (ac != 1)
		return (ft_putstr_fd("Error\nBirden fazla girdi girilemez\n", 2),
			FALSE);
	if (get_env(env, &shell) == FALSE)
		return ((FALSE));
	// free_env(&shell);
	end_malloc(shell.block);
	return (TRUE);
}