/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:54:53 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/19 17:17:43 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd(t_env *env)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        return (("%s\n", cwd), TRUE);
    else
        return (printf("Error\n"), FALSE); //BURAYA DOĞRU ERROR MESAJI YAZILACAK
}