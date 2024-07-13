/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:47 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/14 00:58:50 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>

//static char *remove_quotes_from_content(char *content, char quote)
//void unquote_the_output(t_lexer *lexer)

void	ft_lstadd_parser(t_command **lst, t_command *new)
{
	t_command	*ptr;

	if (*lst == NULL)
	{	
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	new->next = NULL;
}

