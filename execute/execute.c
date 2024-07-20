#include "../minishell.h"

void builtin_start(t_mshell *shell , t_command *command)
{
    if((ft_strcmp(command->args[0], "echo") == 0) || (ft_strcmp(command->args[0], "ECHO") == 0))
       echo(shell);
   /*  else if((ft_strcmp(command->args[0], "env") == 0) || (ft_strcmp(command->args[0], "ENV") == 0))
        builtin_env();
    else if((ft_strcmp(command->args[0], "pwd") == 0) || (ft_strcmp(command->args[0], "PWD") == 0))
        builtin_pwd(); */
    else if(ft_strcmp(command->args[0], "cd") == 0)
        cd(shell);
    /* else if(ft_strcmp(command->args[0], "unset") == 0)
        builtin_unset();
    else if(ft_strcmp(command->args[0], "export") == 0)
        builtin_export();
    else if(ft_strcmp(command->args[0], "exit") == 0)
        builtin_exit(); */
}


int builtin_control(char *command)
{
    if((ft_strcmp(command , "echo") == 0 ) || (ft_strcmp(command , "ECHO") == 0 ))
        return(TRUE);
    else if((ft_strcmp(command , "pwd") == 0) || (ft_strcmp(command , "PWD") == 0 ))
        return(TRUE);
    else if((ft_strcmp(command , "env") == 0) || (ft_strcmp(command , "ENV") == 0 ))
        return(TRUE);
    else if(ft_strcmp(command , "cd") == 0)
        return(TRUE);
    else if(ft_strcmp(command , "exit") == 0)
        return(TRUE);
    else if(ft_strcmp(command , "unset") == 0)
        return(TRUE);
    else if(ft_strcmp(command , "export") == 0)
        return(TRUE);
    return(FALSE);
}

int pipe_check(t_command **command)
{
    if((*command)->prev || (*command)->next || (builtin_control((*command)->args[0]) == FALSE))
        return(TRUE);
    return(FALSE);
}


void execve_start(t_mshell *shell, t_command *command)
{
    char *path = find_path(shell, &command);
    printf("%s\n", path);
}


static int executive(t_mshell *shell,t_command **command)
{
    if(builtin_control((*command)->args[0]) == TRUE)
        builtin_start(shell ,(*command));
    //if(pipe_check(&(*command)) == TRUE)
    //execve_start(shell, (*command));
    (void)shell;
    return(0);
}

void execute(t_mshell *shell)
{
    t_command *command;

    command = shell->command;
    while(command != NULL)
    {
        executive(shell ,&command);
        command = command->next;
    }
}