#include "../minishell.h"
#include <unistd.h>

void	builtin_start(t_mshell *shell, t_command *command)
{
	if ((ft_strcmp(command->args[0], "echo") == 0)
		|| (ft_strcmp(command->args[0], "ECHO") == 0))
		echo(command);
	else if((ft_strcmp(command->args[0], "env") == 0)
		|| (ft_strcmp(command->args[0], "ENV") == 0))
		env(shell->env, command);
	else if ((ft_strcmp(command->args[0], "pwd") == 0)
		|| (ft_strcmp(command->args[0], "PWD") == 0))
		pwd();
	else if (ft_strcmp(command->args[0], "cd") == 0)
		cd(shell);
	 else if(ft_strcmp(command->args[0], "unset") == 0)
			unset(shell);
		else if(ft_strcmp(command->args[0], "export") == 0)
			export(shell);
		/* else if(ft_strcmp(command->args[0], "exit") == 0)
			exit(); */
}

int	builtin_control(char *command)
{
	if ((ft_strcmp(command, "echo") == 0) || (ft_strcmp(command, "ECHO") == 0))
		return (TRUE);
	else if ((ft_strcmp(command, "pwd") == 0) || (ft_strcmp(command,
				"PWD") == 0))
		return (TRUE);
	else if ((ft_strcmp(command, "env") == 0) || (ft_strcmp(command,
				"ENV") == 0))
		return (TRUE);
	else if (ft_strcmp(command, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "export") == 0)
		return (TRUE);
	return (FALSE);
}

static void parent_pipe_update(t_pipe *node, t_command *command) 
{
    if (node && node->prev && command->prev)
	{
		printf("9\n");
        close(node->prev->fd[0]);
        close(node->prev->fd[1]);
    }
	if (node && !command->next)
	{
        close(node->fd[0]);
        close(node->fd[1]);
    }
}

int	pipe_check(t_command **command)
{
	if (((*command)->prev || (*command)->next) || (builtin_control((*command)->args[0]) == FALSE))
		return (TRUE);
	/* else if(builtin_control((*command)->args[0]) == FALSE)
		just_one_cmd() */
	return (FALSE);
}

void	execve_start(t_mshell *shell, t_command *command, t_pipe *node,char **env)
{
	char	*path;
	int pid;

	path = find_path(shell, &command);
	//check_path
	pid = fork();
	if(pid == -1)
		perror("fork");
	if (pid == 0) 
	{
		 if (node && node->prev && node->index > 0)
        {
			printf("1\n");
			link_read_end(node->prev);
		}
        else if (node && node->next && node->index < shell->pipe_count - 1)
        {
			printf("4\n");
			link_write_end(node->next);
		}
		else if(node && !node->prev && !node->next && command->next && !command->prev)
		{
			printf("2\n");
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
		}
		else if(node && !node->prev && !node->next && command->prev && !command->next)
		{
			printf("3\n");
			close(node->fd[1]);
			dup2(node->fd[0], STDIN_FILENO);
			close(node->fd[0]);
		}
        execve(path, command->args, env);
        exit(0);
    }
	parent_pipe_update(node, command);
	waitpid(-1, NULL, 0);
}


// receive a single pointer
// açılmış olan diğer dosya fd lerinin nerde kapanacağı ayarlanıcak
// open_file da kapanmış da olabilir kontrol edilecek
static int	executive(t_mshell *shell, t_command *command, t_pipe *node,char **env)
{
	if (command->args[0])
	{
			if (builtin_control(command->args[0]) == TRUE)
		{
			builtin_start(shell, command);
		}
	}
	if(pipe_check(&command) == TRUE)
		execve_start(shell, command, node ,env);
	save_restore_fd(STDIN_FILENO, STDOUT_FILENO, 1);
	return (0);
}

// command freelenicek
void	execute(t_mshell *shell, char **env)
{
	t_command *command;
	int index;

	command = shell->command;
	index = 0;
	while (command != NULL)
	{
		executive(shell, command, shell->pipe ,env); // pass command directly
		command = command->next;
		if(index % 2 == 0 && shell->pipe && shell->pipe->next != NULL)
			shell->pipe = shell->pipe->next;
	}

}