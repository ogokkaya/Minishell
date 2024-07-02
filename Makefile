NAME = minishell
LIBFT = libft
LIBFTA = libft/libft.a
MINISHELLA = minishell.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c memory_monitor/allocate.c  memory_monitor/memory_utils.c \
		env/env_utils.c env/get_env.c
		
OBJS = $(CFILES:.c=.o)

BOLD_YELLOW	=	\033[1;33m
BOLD_GREEN  =	\033[0;32m
NO_COLOR	=	\033[0m

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@echo "🚧 $(BOLD_YELLOW)Make: Starting the MINISHELL compilation..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(MINISHELL) -o $(NAME)
	@echo "📟 $(BOLD_GREEN)Minishell ready$(NO_COLOR)!"

all: $(NAME)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJS)
	@echo "🧼 $(BOLD_YELLOW)Minishell Clean: $(NO_COLOR)Removed object files"

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "🧼 $(BOLD_YELLOW)Minishell Clean: $(NO_COLOR)Removed all!"

re: fclean all