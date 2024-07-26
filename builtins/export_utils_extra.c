/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:02:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/26 18:02:14 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *fill_name(t_command *command, int i, int j, int equal)
{
    char *name;
 
    name = ft_substr(command->args[i], 0, j + 1);
    if (equal == 1 && !command->args[i][j + 1] &&
             (!ft_strncmp(name, command->args[i], j)) == 0)
        return (free(name), ft_substr(command->args[i], 0, j + 1));
    else
        return (free(name), ft_substr(command->args[i], 0, j));
}

char *fill_content(t_command *command, int i, int j, int equal)
{
    char *content;

     if (equal == 1 && !command->args[i][j + 1])
        content = ft_strdup("");
    else
        content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i]) - j);
    return (content);
}


 void	only_export(t_env *env)
{
	int	i;

	i = 0;
 
    if (!(env->name[0] == '_' && !env->name[1]))
    {
	    while (env && env->name[0])
	    {
	    	ft_putstr_fd("declare -x ", 1);
	    	ft_putstr_fd(env->name, 1);
	    	if (env->content && env->content[0] == '\0')
	    	{
	    		ft_putstr_fd("=\"", 1);
	    		ft_putstr_fd("\"", 1);
	    	}
	    	if (env->content && env->content[0] != '\0')
	    	{
	    		ft_putstr_fd("=\"", 1);
	    		ft_putstr_fd(env->content, 1);
	    		ft_putstr_fd("\"", 1);
	    	}
	    	ft_putstr_fd("\n", 1);
	    	env = env->next;
	    }
    }
}
