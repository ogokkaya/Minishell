/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:49:42 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 17:50:48 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>

t_block	*malloc_starter(void)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		return (perror(MALLOC), exit(EXIT_FAILURE), NULL);
	return (block);
}

int	my_malloc(t_block *block, void *address)
{
	t_block	*new_block;

	if (address != NULL)
	{
		if (block == NULL)
			return (free(address), FALSE);
		new_block = ft_lstnew_memory(address);
		if (new_block != NULL)
		{
			ft_lstadd_back_memory(&block, new_block);
			return (TRUE);
		}
		return (free(address), FALSE);
	}
	return (FALSE);
}

void	free_command_args(t_command *command)
{
	int	i;

	i = 0;
	while (command != NULL)
	{
		while (command->args[i] != (void *)0)
		{
			if (command->args[i])
				free(command->args[i]);
			i++;
		}
		if (command->args)
			free(command->args);
		command = command->next;
		i = 0;
	}
}

void	end_malloc(t_mshell *shell)
{
	free_env(shell);
	ft_lstclear_memory(&shell->block, free);
	rl_clear_history();
}
