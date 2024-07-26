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
    expander_free(var_name, expand, dollar_changed);
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
        ft_putstr_fd(buffer, writig_tip);
        ft_putstr_fd("\n", writig_tip);
        if(buffer)
            free(buffer);
    }
    // signal gelmeli bu kısma yada heredoc_start a eklenecek
    // leak durumları düşünülmeli
}

// düzenlenicek
/* int heredoc_start(t_mshell *shell, char *delimiter,t_pipe *node) 
{
    int exit_status;
    int pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) { // Child process
        close(node->fd[0]); // Close read end
        write_to_pipe(shell, delimiter, node->fd[1]);
        close(node->fd[1]);
        exit(0);
    } else { // Parent process
        close(node->fd[1]); // Close write end
        waitpid(pid, &exit_status, 0);
        exit_status = WEXITSTATUS(exit_status);
        if (exit_status != 0) {
            close(node->fd[0]);
            return -1;
        }
        dup2(node->fd[0], STDIN_FILENO);
    }
    return 0;
}

void	pipe_dup_create(t_pipe *node)
{
    int pipe_status;

    pipe_status = pipe(node->fd);
    if(pipe_status == -1)
        perror("pipe");
}

void	ft_lstadd_back_pipe(t_pipe **lst, t_pipe *new)
{
	t_pipe	*ptr;
    int index;

    index = 1;
	if (*lst == NULL)
	{
		*lst = new;
        new->index = index;
		new->prev = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
		{
            ptr = ptr->next;
            index++;
        }
		ptr->next = new;
        new->index = index;
        ptr->fd[0] = new->fd[0];
        ptr->fd[1] = new->fd[1];
		new->prev = ptr;
	}
	new->next = NULL;
}


void	*pipe_create(t_mshell *shell)
{
    t_pipe *new_pipe;

    new_pipe = ft_calloc(1, sizeof(t_pipe));
    pipe_dup_create(new_pipe);
    ft_lstadd_back_pipe(&shell->pipe, new_pipe);
    return(new_pipe);
}

void parser_heredoc_start(t_mshell *shell, t_lexer *lexer)
{
    t_pipe *node;
    //int heredoc_index;
    //int std_in;

    //heredoc_index = 0;
    //std_in = STDIN_FILENO;
    node = NULL;
    while(lexer != NULL)
	{
		if(lexer->type == TOKEN_HEREDOC && lexer->next != NULL)
		{
            lexer = lexer->next;
            //heredoc_index++;
            node = pipe_create(shell);
            heredoc_start(shell, lexer->content, node);
        }
		lexer = lexer->next;
	}
    // close(stdin);
    // bunu düşünücem
}
*/

int heredoc_start(t_mshell *shell, char *delimiter, int std_in , t_pipe *node) 
{
    int exit_status;
    pid_t pid;

    pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        return -1;
    }
    if (pid == 0) // Child process
    {
        close(node->fd[0]); // Close read end
        write_to_pipe(shell, delimiter, node->fd[1]);
        close(node->fd[1]);
        exit(0);
    } // Parent process 
    close(node->fd[1]); // Close write end
    waitpid(pid, &exit_status, 0);
    exit_status = WEXITSTATUS(exit_status);
    if (exit_status != 0) 
    {
        close(node->fd[0]);
        return -1;
    }
    if(node && node->index > 0)
    {
        if(node->next)
            node->next->fd[0] = node->fd[0];
    }
    else
    {
        dup2(node->fd[0], std_in);
        close(node->fd[0]);
    }
    return 0;
}



void pipe_dup_create(t_pipe *node)
{
    if (pipe(node->fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}



void ft_lstadd_back_pipe(t_pipe **lst, t_pipe *new)
{
    t_pipe *ptr;
    int index = 1; 

    if (*lst == NULL) 
    {
        *lst = new;
        new->index = 1;
        new->prev = NULL;
    } 
    else 
    {
        ptr = *lst;
        while (ptr->next != NULL) 
        {
            ptr = ptr->next;
            index++;
        }
        ptr->next = new;
        new->index = index;
        new->prev = ptr;
    }
    new->next = NULL;
}


void    pipe_create(t_mshell *shell)
{
    t_pipe *new_pipe;
    int index;

    index = 0;
    while (index < shell->pipe_count)
    {
        new_pipe = ft_calloc(1, sizeof(t_pipe));
        if (!new_pipe) {
            perror("calloc");
            exit(EXIT_FAILURE);
        }
        pipe_dup_create(new_pipe);
        ft_lstadd_back_pipe(&shell->pipe, new_pipe);
        my_malloc(shell->block, new_pipe);
        index++;
    }
}

void parser_heredoc_start(t_mshell *shell, t_lexer *lexer, t_pipe *node)
{
    int std_in;
    int heredoc_count;

    std_in = STDIN_FILENO;
    heredoc_count = 0;
    while (lexer != NULL) 
    {
        if (lexer->type == TOKEN_HEREDOC && lexer->next != NULL && node)
        {
            lexer = lexer->next;
            heredoc_count++;
            if (heredoc_start(shell, lexer->content, std_in , node) == -1)
            {
                fprintf(stderr, "Heredoc failed for delimiter: %s\n", lexer->content);
                return; // Hata durumunda işlemi sonlandırabiliriz.
            }
            if(heredoc_count > 1 && node->next)
            {
                std_in = node->fd[0];
                node = node->next;
            }
        }
        lexer = lexer->next;
    }
}
