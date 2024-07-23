/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:51 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/23 12:30:30 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>

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
# define MALLOC "Error\nCould not allocate memory\n"
# define ARG "Error\nThe program can only run without arguments\n"
#define NSFD "No such file or directory\n"
#define CNF "command not found\n"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC

}						t_token_type;

// ENV STRUCT
typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

// LEXER STRUCT
typedef struct s_lexer
{
	char				*content;
	t_token_type		type;
	struct s_lexer		*next;
}						t_lexer;

// MEMORY STRUCT
typedef struct s_block
{
	void				*allocate;
	struct s_block		*next;
}						t_block;

typedef struct s_redirection
{
	int						redir_fd;
	int						r_stdin;
	int						r_stdout;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}						t_redirection;

typedef struct s_command // echo test > test.txt | cat wc -l
{
	char **args;
	t_redirection *redirection;
	int pipe_fd[2];
	struct s_command *next;
	struct s_command *prev;
}						t_command;

// MAIN STRUCT
typedef struct s_mshell
{
	char				*input;
	struct s_block		*block;
	struct s_command	*command;
	struct s_lexer		*lexer;
	struct s_env		*env;
	struct s_ast		*ast;
}						t_mshell;

// input_control
int						line_verify(char *line);
int						ft_space(char c);

// memory monitor
void					*my_malloc(t_block *block, void *address);
void					free_malloc(t_block *block, void *delete_adress);
void					ft_lstdelone_memory(t_block *lst, void (*del)(void *));
void					end_malloc(t_mshell *shell);
t_block					*ft_lstnew_memory(void *content);
void					ft_lstadd_back_memory(t_block **lst, t_block *new);
void					ft_lstclear_memory(t_block **lst, void (*del)(void *));
t_block					*malloc_starter(void);

// error handling
void					error_exit(char *error_message, t_mshell *shell,
							int free_flag);

// env
t_env					*ft_lstnew_env(char *str, char *ptr);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
int						get_env(char **env, t_mshell *shell);
void					free_env(t_mshell *shell);
void					change_env(t_mshell *shell, char *name, char *content);
//void					add_env(t_mshell *shell, char *name, char *content);

// lexer
void					lexer(t_mshell *shell);
t_lexer					*ft_lstnew_lexer(t_mshell *shell, char *content,
							t_token_type type);
void					ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

// expander
void					expander(t_mshell *shell, t_lexer *lexer);
void 					expander_free(void  *address, void *address_1, void *address_2);
int						*exit_status(void);
int						check_quotes(const char *before, const char *after);
int 					count_char(const char *str, char quote);
char					*find_env(t_mshell *shell, char *path);
char					*ft_strchr_dollar(const char *s);

// execute
char					*find_path(t_mshell *shell, t_command **command);
void					execute(t_mshell *shell);
void 					perror_write(char *content, char *perror);
void					save_restore_fd(int std_in, int std_out, int mode);

// parser
// t_ast   	*create_parser_node(t_lexer *lexer);
// void		ft_listadd_back_ast(t_ast **lst, t_ast *new);
void					parser(t_mshell *shell);
int						heredoc_start(t_mshell *shell, char *delimeter);
void					parser_init(t_mshell *shell, t_lexer **lexer);
void					unquote_the_output(t_mshell *shell, t_lexer *lexer);

// builtin
int						cd(t_mshell *shell);
int						echo(t_mshell *shell);
int						pwd(void);
int						env(t_env *env, t_command *command);
int						unset(t_mshell *shell);
int						export(t_mshell *shell);
void					if_exist(t_env *env, char *content);
void					if_not_exist(t_mshell *shell, t_env *env, char *name, char *content);
int						id_validation(char *name, char *content ,int equal);
int						is_equal(char c);
#endif