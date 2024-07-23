#include "../minishell.h"
#include <unistd.h>


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