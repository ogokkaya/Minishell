#include "../minishell.h"
#include <unistd.h>

static void	free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*path_env(t_env *env)
{
	char	*sub;

	while (env != NULL && ft_strncmp(env->name, "PATH", 4))
        env = env->next;
	sub = ft_substr(env->content, 0, ft_strlen(env->content));
	if (!sub)
		return (NULL);
	return (sub);
}

static char	*cmd_and_path(char *cmd, char **path)
{
	char	*sub;
	char	*cmd_and_path;
	int		i;

	sub = ft_strjoin("/", cmd);
	if (!sub)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmd_and_path = ft_strjoin(path[i], sub);
		if (access(cmd_and_path, X_OK) == 0)
				return (free(sub), cmd_and_path);
		free(cmd_and_path);
		i++;
	}
	return (free(sub), NULL);
}

char	*find_path(t_mshell *shell, t_command **command)
{
    char    *find_path;
	char	**path;
	char	*sub;
	char	**cmd1;

	cmd1 = (*command)->args;
	sub = path_env(shell->env);
	if (!sub)
		return (free(cmd1), NULL);
	path = ft_split(sub, ':');
	if (!path)
		return (free(sub), free_str(cmd1), NULL);
	free(sub);
	find_path = cmd_and_path(*cmd1, path);
	free_str(path);
	free_str(cmd1);
	if (!find_path)
	{
		ft_putstr_fd("Access: There is no way\n", 2);
		return (NULL);
	}
	return (find_path);
}