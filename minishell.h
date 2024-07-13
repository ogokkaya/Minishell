/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:51 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/14 00:58:59 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

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
# define PROMT "minishell$"
//ERROR
# define MALLOC "Error\nCould not allocate memory\n"
#define ARG "Error\nThe program can only run without arguments\n"

typedef enum s_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC
	
} t_token_type;

//ENV STRUCT
typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

//LEXER STRUCT
typedef struct s_lexer
{
	char			*content;
	t_token_type 	type;
	struct s_lexer	*next;
}			t_lexer;

//MEMORY STRUCT
typedef struct s_block
{
	void			*allocate;
	struct s_block	*next;
}					t_block;

typedef struct s_redirection
{
	char *content;
	int redir_fd;
	int flags;
}	t_redirection;

typedef struct s_file
{
	int	inp_fd;
	int	out_fd;
	int	*prev_file;
	int	*next_file;
}	t_file;

typedef struct s_command // echo test > test.txt | cat wc -l
{
	char 				**args;
	t_redirection		*redirection;
	t_file				file;
	struct s_command	*next;
	struct s_command 	*prev;
} t_command;

//MAIN STRUCT
typedef struct s_mshell
{
	char			*input;
	struct s_block	*block;
	struct s_command *command;
	struct s_lexer  *lexer;
	struct s_env	*env;
	struct s_ast	*ast;
}					t_mshell;

// input_control
int			line_verify(char *line);
int			ft_space(char c);


// memory monitor
void				*my_malloc(t_block *block, void *address);
void				free_malloc(t_block *block, void *delete_adress);
void				ft_lstdelone_memory(t_block *lst, void (*del)(void *));
void				end_malloc(t_mshell *shell);
t_block				*ft_lstnew_memory(void *content);
void				ft_lstadd_back_memory(t_block **lst, t_block *new);
void				ft_lstclear_memory(t_block **lst, void (*del)(void *));
t_block				*malloc_starter(void);

// error handling
void				error_exit(char *error_message, t_mshell *shell,
						int free_flag);

// env
t_env				*ft_lstnew_env(char *str, char *ptr);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
int					get_env(char **env, t_mshell *shell);
void				free_env(t_mshell *shell);

// lexer
void 		lexer(t_mshell *shell);
t_lexer	*ft_lstnew_lexer(t_mshell *shell ,char *content, t_token_type type);
void	ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

//expander
void expander(t_mshell *shell, t_lexer *lexer);
int *exit_status(void);
int check_quotes(const char *before, const char *after);
char *find_env(t_mshell *shell, char *path);
char	*ft_strchr_dollar(const char *s);



//parser
//t_ast   	*create_parser_node(t_lexer *lexer);
//void		ft_listadd_back_ast(t_ast **lst, t_ast *new);
void		parser(t_mshell *shell);
void	ft_lstadd_parser(t_command **lst, t_command *new);

//void		unquote_the_output(t_lexer *lexer);


#endif