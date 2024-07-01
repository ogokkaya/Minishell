/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:49:42 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/01 16:34:54 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

#include <stdio.h>

//Mallocs the starter block
t_block *malloc_starter()
{
    t_block *block = (t_block *)malloc(sizeof(t_block));

    if (!block)
        return (NULL);
    
    block->allocate = NULL;
    block->next = NULL;
    return (block);
}

//Mallocs the memory and returns the pointer
void  *my_malloc(t_block *block, size_t size)
{
    if (block == NULL)
        return (NULL);
    
    void *ptr;

    ptr = malloc(size);
    
    if (ptr != NULL)
    {
        t_block *new_block = (t_block *)malloc(sizeof(t_block));

        if (new_block != NULL)
        {
            new_block->allocate = ptr;
            new_block->next = block->next;
            block->next = new_block;
        }
    }
    return (ptr);
}

//Free's the malloced memory node
void    *free_malloc(t_block *block, void *delete_adress)
{
    if (block == NULL || delete_adress == NULL)
        return (NULL);
    
    t_block *current_node = block;
    t_block *previous_node = NULL;

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
    
}

//Free's all the malloced memory and the block
void    *end_malloc(t_block *block)
{
    if (block->next != NULL)
        end_malloc(block->next);
    if (block->allocate != NULL)
        free(block->allocate);
    free(block);
}