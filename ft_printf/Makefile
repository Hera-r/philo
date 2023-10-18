SRCS    = ft_printf.c numerique.c alpha.c format.c
OBJS    = ${SRCS:.c=.o}
CC    = cc
RM    = rm -f
CFLAGS    = -Wall -Wextra -Werror
NAME    = libftprintf.a

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}: ${OBJS}
		ar rc ${NAME} ${OBJS}

all:    ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:        fclean all

.PHONY:    all clean fclean re