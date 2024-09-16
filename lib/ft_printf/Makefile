NAME = libftprintf.a

SRCS = ft_printf.c\
			ft_printf_utils.c\
			ft_hexa_base.c\
					

OBJS =          ${SRCS:.c=.o}

CFLAGS =        -Wall -Wextra -Werror

all:            ${NAME}

${NAME}:        ${OBJS}
				ar rc ${NAME} ${OBJS}

${OBJS_BONUS}:
				cc ${CFLAGS} -c -I.

${OBJS}:
				cc ${CFLAGS} ${SRCS} -c -I.

clean:
				rm -rf ${OBJS}

fclean:         clean
				rm -rf ${NAME}

re:             fclean all

.PHONY:         all clean fclean re
