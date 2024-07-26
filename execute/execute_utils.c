#include "../minishell.h"
#include <unistd.h>

/* void link_write_end(t_pipe *node)
{
	close(node->fd[0]);
	dup2(node->fd[1], STDOUT_FILENO);
	close(node->fd[1]);
}

void link_read_end(t_pipe *node)
{
	close(node->fd[1]);
	dup2(node->fd[0], STDIN_FILENO);
	close(node->fd[0]);
} */


void link_read_end(t_pipe *node) 
{
    close(node->fd[1]);
    dup2(node->fd[0], STDIN_FILENO);
    close(node->fd[0]);
}

void link_write_end(t_pipe *node) 
{
    close(node->fd[0]);
    dup2(node->fd[1], STDOUT_FILENO);
    close(node->fd[1]);
}

void perror_write(char *content, char *perror)
{
	if(content)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(content, 1);
		ft_putstr_fd(":", 1);
		ft_putstr_fd(perror, 1);
		*exit_status() = 127;
	}
}

void	save_restore_fd(int std_in, int std_out, int mode)
{
	static int	saved_stdin;
	static int	saved_stdout;
	if (mode == 0)
	{
		saved_stdin = dup(std_in);
		saved_stdout = dup(std_out);
	}
	if (mode == 1)
	{
		dup2(saved_stdin, std_in);
		close(saved_stdin);
		dup2(saved_stdout, std_out);
		close(saved_stdout);
	}
}
