NAME = minishell
LIBFT = libft
LIBFTA = libft/libft.a
MINISHELLA = minishell.h
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c memory_monitor/allocate.c  memory_monitor/memory_utils.c \
		env/env_utils.c env/get_env.c \
		expander/expander.c lexer/lexer.c lexer/lexer_utils.c error_handling/error_handler.c

		
		
OBJS = $(CFILES:.c=.o)

BOLD_YELLOW	=	\033[1;33m
BOLD_GREEN  =	\033[0;32m
NO_COLOR	=	\033[0m

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@echo "🚧 $(BOLD_YELLOW)Make: Starting the MINISHELL compilation..."
	@$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFTA) $(MINISHELL) -o $(NAME)
	@clear
	@echo "📟 $(BOLD_GREEN)Minishell compiled succesfully$(NO_COLOR)!"

all: $(NAME)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJS)
	@clear
	@echo "🧼 $(BOLD_YELLOW)Minishell Clean: $(NO_COLOR)Removed object files"

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@clear
	@echo "🧼 $(BOLD_YELLOW)Minishell Clean: $(NO_COLOR)Removed all!"

re: fclean all