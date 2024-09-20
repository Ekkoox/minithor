NAME = libftprintf.a

SRCS = ft_printf.c\
			ft_printf_utils.c\
			ft_hexa_base.c\
					

OBJS =          ${SRCS:.c=.o}

CFLAGS =        -Wall -Wextra -Werror

all:            ${NAME}

$(NAME):
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar -rc $(NAME) $(OBJS)
	@echo "Compiled $(NAME) & .o."


bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) -c $(BONUS)
	ar -rc $(NAME) $(OBJS_BONUS)

.c.o:
	cc ${CF} -c $^ -include ${HEADER}

clean:
	@rm -f $(OBJS_BONUS) $(OBJS) 
	@echo "Deleted .o files."

fclean: clean
	@rm -f $(NAME)
	@echo "Deleted $(NAME)."

re:             fclean all

.PHONY:         all clean fclean re