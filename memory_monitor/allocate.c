/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:49:42 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/01 18:10:07 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// Mallocs the starter block
t_block	*malloc_starter(void)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		return (NULL);
	return (block);
}

// Mallocs the memory and returns the pointer
void	*my_malloc(t_block *block, size_t size)
{
	void	*ptr;
	t_block	*new_block;

	if (block == NULL)
		return (NULL);
	ptr = malloc(size);
	if (ptr != NULL)
	{
		new_block = (t_block *)malloc(sizeof(t_block));
		if (new_block != NULL)
		{
			new_block->allocate = ptr;
			new_block->next = block->next;
			block->next = new_block;
			// DOĞRU DURUMDA ÇIKIŞ İÇİN
			return (ptr);
		}
	}
	return (printf(MALLOC), ptr);
}

// Free's the malloced memory node
void	*free_malloc(t_block *block, void *delete_adress)
{
	t_block	*current_node;
	t_block	*previous_node;

	if (block == NULL || delete_adress == NULL)
		return (NULL);
	current_node = block;
	previous_node = NULL;
	while (current_node != NULL && current_node->allocate != delete_adress)
	{
		previous_node = current_node;
		current_node = current_node->next;
	}
	if (current_node != NULL)
	{
		if (previous_node != NULL)
			block = current_node->next;
		else
			previous_node->next = current_node->next;
		if (current_node->allocate != NULL)
			free(current_node->allocate);
		free(current_node);
	}
	return (NULL);
}

// Free's all the malloced memory and the block
void	end_malloc(t_block *block)
{
	if (block->next != NULL)
		end_malloc(block->next);
	if (block->allocate)
		free(block->allocate);
	free(block);
}
