/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:51 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/07 19:21:32 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <sys/_types/_size_t.h>
# include <unistd.h>

# define TRUE 0
# define FALSE 1

// LEXER_DEFINES
# define SPACE ' '
# define PIPE '|'
# define BRACKET_OPEN '('
# define BRACKET_CLOSE ')'
# define REDIRECT_OUT '>'
# define REDIRECT_IN '<'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

// PRINT_DEFINES
# define PROMT "minishell$ "
// ERROR
# define MALLOC " Error\nCould not allocate memory\n"
# define ARG " Error\nThe program can only run without arguments\n"
# define NSFD " No such file or directory\n"
# define CNF " command not found\n"
# define DRCTRY " is a directory\n"
# define PRMDNED " Permission denied\n"
# define HMNTSET " HOME not set\n"
# define SYSERROR "syntax error near unexpected token\n"
# define TMA "exit: too many arguments\n"
# define NAVI "export: not a valid identifier\n"
# define NIVM "not a valid identifier\n"

// SIGNAL
# define SIGHEREDOC 2
# define SIGPROMT 3
# define SIGEXEC 4
# define SIGEXIT 130
# define SIGSTRT 0

extern int				g_signal_flag;

typedef enum s_quotes
{
	NOT_QUOTED,
	IN_SINGLE,
	IN_DOUBLE
}						t_quotes;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_FORK
}						t_token_type;

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct s_lexer
{
	char				*content;
	t_token_type		type;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_export_vars
{
	int					i;
	int					j;
	int					equal;
	char				*name;
	char				*content;
}						t_export_vars;

typedef struct s_unset_vars
{
	t_env				*tmp;
	t_env				*prev;
	char				*name;
	int					found;
	int					i;
	t_env				*next;
}						t_unset_vars;

typedef struct s_get_env_vars
{
	char				*name;
	char				*content;
	t_env				*new_env;
	char				*equal_value;
	size_t				char_len;
}						t_get_env_vars;

typedef struct s_block
{
	void				*allocate;
	struct s_block		*next;
}						t_block;

typedef struct s_pipe
{
	int					fd[2];
	int					index;
	struct s_pipe		*next;
	struct s_pipe		*prev;
}						t_pipe;

typedef struct s_command
{
	char				**args;
	int					input;
	int					output;
	int					control;
	int					child_pid;
	int					heredoc;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_mshell
{
	char				*input;
	int					qoute_status;
	struct s_block		*block;
	struct s_command	*command;
	struct s_lexer		*lexer;
	struct s_env		*env;
	int					shlvl;
}						t_mshell;

typedef struct s_variables
{
	int					i;
	int					j;
	int					k;
	char				c;
	char				s;
	char				*str;
	char				*str1;
	char				*tmp;
}						t_variables;

// input_control
int						line_verify(char *line);
int						ft_space(char c);
int						in_out_check(t_variables *vars, char *line);
void					j_0c_null(t_variables *vars, char **line);
void					j_1i_0(t_variables *vars);

// memory monitor
int						my_malloc(t_block *block, void *address);
void					ft_lstdelone_memory(t_block *lst, void (*del)(void *));
void					end_malloc(t_mshell *shell);
t_block					*ft_lstnew_memory(void *content);
void					ft_lstadd_back_memory(t_block **lst, t_block *new);
void					ft_lstclear_memory(t_block **lst, void (*del)(void *));
t_block					*malloc_starter(void);

// env
t_env					*ft_lstnew_env(char *str, char *ptr);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
int						get_env(char **env, t_mshell *shell);
void					free_env(t_mshell *shell);
void					change_env(t_mshell *shell, char *name, char *content);
void					mimic_bash(t_mshell *shell);

// main
int						loop_shell(t_mshell *shell);

// lexer
void					lexer(t_mshell *shell);
t_lexer					*ft_lstnew_lexer(t_mshell *shell, char *content,
							t_token_type type);
void					ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

// expander
void					expander(t_mshell *shell, t_lexer *lexer);
int						*exit_status(void);
t_quotes				quote_check(const char *str, size_t start);
int						count_char(const char *str, char quote);
char					*find_env(t_mshell *shell, char *path);
char					*ft_strchr_dollar(const char *s);

// execute
char					*find_path(t_mshell *shell, t_command *command);
void					execute(t_mshell *shell);
void					multiple_execute(t_mshell *shell, t_command *command,
							t_lexer *lexer);
void					duplicate(t_command *command);
void					print_err_pipe_and_fork(int flag);
void					pipe_or_die(t_mshell *shell, int *fd);
pid_t					fork_or_die(t_mshell *shell);
void					perror_write(char *content, char *perror);
int						builtin_control(t_command *cmd, char *command);
void					builtin_start(t_mshell *shell, t_command *command,
							int flag);
int						check_path(char *path);
void					child_control(t_mshell *shell);
int						path_exists(const char *path);
int						can_execute(const char *path);
int						is_directory(const char *path);
void					print_error(char *cmd, int flag);
void					print_error2(int flag, char *cmd);
void					free_str(char **str);
char					**execute_env(t_mshell *shell);
int						ft_lstsize_env(t_env *lst);

// parser
void					parser(t_mshell *shell);
void					heredoc_start_before(t_mshell *shell,
							t_command *command, t_lexer *lexer);
void					heredoc_start(t_mshell *shell, char *delimiter,
							t_command *command);
void					write_to_pipe(t_mshell *shell, char *delimeter,
							int writig_tip);
void					parser_init(t_mshell *shell, t_lexer **lexer);
void					unquote_the_output(t_mshell *shell, t_lexer *lexer);
void					file_creation(t_mshell *shell, t_command *command,
							t_lexer **lexer);
int						file_check(char *path);

// builtin
void					cd(t_command *command, t_mshell *shell);
void					echo(t_command *command);
void					pwd(t_command *command);
void					env(t_env *env, t_command *command);
void					unset(t_env **env, t_command *command);
void					export(t_mshell *shell, t_command *command);
void					if_not_exist(t_mshell *shell, char *name,
							char *content);
int						id_validation(char *command);
void					ft_exit(t_mshell *shell, t_command *command);

// builtins/export_utils_extra.c
char					*fill_name(t_command *command, int i, int j, int equal);
char					*fill_content(t_command *command, int i, int j,
							int equal);
void					only_export(t_env *env, t_command *command);
t_env					*ft_lstnew_export_env(char *str, char *ptr);
void					signal_init(void);
int						arg_order(char *str);

// memory free
void					free_command_args(t_command *command);

#endif
