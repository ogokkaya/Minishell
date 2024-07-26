/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:27:23 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/26 17:04:20 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env	*ft_lstnew_env(char *str, char *ptr)
{
	t_env	*new;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (0);
	new->name = str;
	new->content = ptr;
	new->next = NULL;
	return (new);
}


