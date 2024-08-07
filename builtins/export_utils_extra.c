/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:02:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 17:29:08 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

char	*fill_name(t_command *command, int i, int j, int equal)
{
	char	*name;

	name = ft_substr(command->args[i], 0, j + 1);
	if (equal == 1 && !command->args[i][j + 1] && (!ft_strncmp(name,
				command->args[i], j)) == 0)
		return (free(name), ft_substr(command->args[i], 0, j + 1));
	else
		return (free(name), ft_substr(command->args[i], 0, j));
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_content;

	temp_name = a->name;
	temp_content = a->content;
	a->name = b->name;
	a->content = b->content;
	b->name = temp_name;
	b->content = temp_content;
}

void	sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	if (head == NULL)
		return ;
	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->name, ptr1->next->name, ft_strlen(ptr1->name)
					+ 1) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

static void	ft_put(t_env *tmp, t_command *command)
{
	ft_putstr_fd("=\"", command->output);
	ft_putstr_fd(tmp->content, command->output);
	ft_putstr_fd("\"", command->output);
}

void	only_export(t_env *env, t_command *command)
{
	t_env	*tmp;

	tmp = env;
	sort_env_list(tmp);
	while (tmp && tmp->name[0])
	{
		if (!(tmp->name[0] == '_' && tmp->name[1] == '\0'))
		{
			ft_putstr_fd("declare -x ", command->output);
			ft_putstr_fd(tmp->name, command->output);
			if (!tmp->content)
			{
				ft_putstr_fd("\n", command->output);
				tmp = tmp->next;
				continue ;
			}
			if (tmp->content && tmp->content[0] == '\0')
				ft_putstr_fd("=\"\"", command->output);
			if (tmp->content && tmp->content[0] != '\0')
				ft_put(tmp, command);
			ft_putstr_fd("\n", command->output);
		}
		tmp = tmp->next;
	}
}
