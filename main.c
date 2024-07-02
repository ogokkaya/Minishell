/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/02 15:56:32 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// burda fonk t_mshell başlat

int	main(int ac, char **av, char **env)
{
	t_mshell shell;

	if (ac != 1)
		return (ft_putstr_fd("Error\nBirden fazla girdi girilemez\n", 2),
			FALSE);
	(void)av;
	shell.env = NULL;
	shell.block = malloc_starter();
	if (get_env(env, &shell) == FALSE)
		return ((FALSE));
	end_malloc(&shell);
	return (TRUE);
}