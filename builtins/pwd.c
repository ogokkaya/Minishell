/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:54:53 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/12 16:56:23 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd(t_env *env)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        return (printf("%s\n", cwd), TRUE);
    else
        return (printf("Error\n"), FALSE); //BURAYA DOĞRU ERROR MESAJI YAZILACAK
}