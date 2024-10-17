NAME = minishell

C_FILES = main.c \
          pipe.c \
          prompt.c \
          pipe_utils.c\
		  token.c\
		  token_utils.c\

BOLD = \033[1m
RED = \033[31m
RESET = \033[0m
BLACK  = \033[30m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
WHITE  = \033[37m

SRCS = $(addprefix srcs/, $(C_FILES))

CFLAGS = -Wall -Werror -Wextra -I includes/ -g

LIB = ft_printf/libftprintf.a libft/libft.a 
DEPS = $(addprefix lib/, $(LIB))

all: $(NAME)

$(NAME): $(SRCS)
	@echo "$(BOLD)$(RED)Compilation des libs...$(RESET)"
	@$(MAKE) --no-print-directory -C lib/libft
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BLUE)||$(RESET)$(GREEN)compilation de la libft fini$(RESET)$(BLUE)||$(RESET)"
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@$(MAKE) --no-print-directory -C lib/ft_printf
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BLUE)|||$(RESET)$(GREEN)compilation de Printf fini$(RESET)$(BLUE)|||$(RESET)"
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BOLD)$(RED)Creation de $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(SRCS) -o $(NAME) $(DEPS) -lreadline
	@echo "$(BOLD)$(YELLOW) COMPILATION TERMINER $(RESET)"

clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	@$(MAKE) --no-print-directory -C lib/libft fclean
	@$(MAKE) --no-print-directory -C lib/ft_printf fclean

fclean: clean
	@echo "Removing executable..."
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
