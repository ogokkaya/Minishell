/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:41 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/03 00:52:04 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void shell_start_init(t_mshell *shell)
{
	shell->env = NULL;
	shell->block = malloc_starter();
}

int	main(int ac, char **av, char **env)
{
	t_mshell shell;

	(void)av;
	if (ac != 1)
		return (printf(ARG),FALSE);
	// ana struct yapısının başlangıcı için fonksiyon eklendi
	shell_start_init(&shell);
	// env split ile alındığında problem yaşandığı için get_env fonk güncellendi
	if (get_env(env, &shell) == FALSE)
		return (printf(MALLOC),FALSE);
	end_malloc(&shell);
	return (TRUE);
}