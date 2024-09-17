NAME = minishell

C_FILES = main.c\
			pipe.c\
			prompt.c\
			pipe_utils.c\

SRCS = $(addprefix srcs/,$(C_FILES))

CFLAGS = -Wall -Werror -Wextra -I includes/ -g

LIB = ft_printf/libftprintf.a libft/libft.a
DEPS = $(addprefix lib/,$(LIB))

all: ${NAME}

${NAME}: ${SRCS}
	make -C lib/libft
	make -C lib/ft_printf
	cc ${CFLAGS} ${SRCS} -o ${NAME} ${DEPS}

clean:
	make -C lib/libft clean
	make -C lib/ft_printf clean

fclean:	clean
		rm -rf ${NAME}

re:             fclean all

.PHONY:         all clean fclean re
