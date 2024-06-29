/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:05:54 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	//push TEST 1

	(void)av;
	if (ac != 1)
		return (ft_putstr_fd("Error\nBirden fazla girdi girilemez\n", 2),
			FALSE);
	while (1)
	{
		readline(shell.input);
		add_history(shell.input);
	}
	return (TRUE);
}