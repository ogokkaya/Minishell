#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <./readline/history.h>
#include <./readline/readline.h>

static void expander_heredoc_env(t_mshell *shell,char **buffer, char *after_dollar, char *before_dollar)
{
    char *var_name;
    char *expand;
    char *dollar_changed;
    int index;
    
    index = 0;
     if(after_dollar[0] == '$' && !ft_isalpha(after_dollar[1]) && (after_dollar[1] != '_'))
    {
        *buffer = ft_strjoin(before_dollar, after_dollar + 2);
        if(!*buffer)
            return(perror("dollar_changed"), exit(1));
        return;
    }
    while(after_dollar[index++])
        if(!ft_isalnum_mshell(after_dollar[index]))
            break;
    var_name = ft_substr(after_dollar , 1, --index);
    expand = find_env(shell, var_name);
    dollar_changed = ft_strjoin(expand, &after_dollar[++index]);
    *buffer = ft_strjoin(before_dollar, dollar_changed);
    free(var_name);
    free(expand);
    free(dollar_changed);
    if(!*buffer)
        return(perror("dollar_changed"),exit(1));
}

static void expander_heredoc(t_mshell *shell, char **buffer)
{
    char *after_dollar;
    char *before_dollar;

    after_dollar = ft_strchr_dollar(*buffer);
    while(after_dollar)
    {
        before_dollar = ft_substr(*buffer, 0, after_dollar - *buffer);
        if(!before_dollar)
            return(perror("expander_heredoc"), exit(1)); // bu kısımlar düşünülecek
        expander_heredoc_env(shell , buffer, after_dollar, before_dollar);
        if(before_dollar)
            free(before_dollar);
        after_dollar = ft_strchr_dollar(*buffer);
    }
}

void write_to_pipe(t_mshell *shell ,char *delimeter, int writig_tip)
{
    char *buffer;

    while(1)
    {
        buffer = readline("heredoc> ");
        if(!buffer || (ft_strcmp(buffer, delimeter) == 0))
            break;
        if(!*buffer)
            buffer = ft_strdup("\n");
        else
            expander_heredoc(shell ,&buffer);
        printf("%s\n", buffer);
        ft_putstr_fd(buffer, writig_tip);
        ft_putstr_fd("\n", writig_tip);
        if(buffer)
            free(buffer);
    }
    // signal gelmeli bu kısma yada heredoc_start a eklenecek
    // leak durumları düşünülmeli
}

int heredoc_start(t_mshell *shell,t_redirection *redirection,char *delimeter)
{
    int exit_status;
    int pid;
    int pipe_fd[2];

    pipe(pipe_fd);
    pid = fork();
    if(pid == -1)
        return(-1);
    if(pid == 0)
    {
        close(pipe_fd[0]);
        write_to_pipe(shell ,delimeter, pipe_fd[1]);
        exit(0);
    }
    close(pipe_fd[1]);
    waitpid(pid , &exit_status, 0);
    exit_status >>= 8;
    if(exit_status != 0)
        return(close(pipe_fd[0]),-1);
    redirection->redir_fd = pipe_fd[0];
    // bu kısıma bakılacak şimdilik 0 da kalıyo bu kısım istenilen fd ye bağlanıcak
    // signal ayarlanıcak
    return (0);
}
