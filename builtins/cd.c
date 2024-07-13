/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:18:18 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/12 16:40:57 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static int cd_updater(t_mshell *shell, char *old_pwd)
{
		if (!old_pwd)
		    return (printf("OLDPWD not set"), 1);
	    	//ft_exit_value(EXIT_SET, 1, 0);
	    if (chdir(old_pwd) == -1)
	    	return (printf("No such file or directory"), 1);

        //BURADA HATA KONTROLLERİ VE CHDIR ILE PWD VE OLDPWD KONTROLLERI YAPILACAK 
        //VE HATA KODU DEĞİŞİP DÖNÜLECEK
            
}

int cd(t_mshell *shell)
{
    char cwd[1024];
    char *pwd;
    char *oldpwd;
    char *path;

    pwd = find_env(shell, "PWD");
    oldpwd = find_env(shell, "OLDPWD");
    if (shell->lexer->next)
        path = shell->lexer->next->content;
    if (chdir(path) == -1)
        return(printf("cd: %s: No such file or directory\n", path), 1);
    else
    {
        if (cd_updater(shell, oldpwd) == -1)
        return (printf("ERROR\n", 1));
    }
    
    //change environment here
    

    printf("PWD: %s\n", pwd);
    printf("OLDPWD: %s\n", oldpwd);
}

int main(int argc, char **argv, char **env)
{
    t_mshell *shell;
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->content = "cd";
    lexer->next = malloc(sizeof(t_lexer));
    lexer->next->content = "srcs";
    lexer = lexer->next;
    cd(lexer);
    return (TRUE);
}