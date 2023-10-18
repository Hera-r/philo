SRCS	= ft_strlen.c ft_isdigit.c ft_strdup.c ft_strcmp.c

OBJS	= ${SRCS:.c=.o}

CC	= cc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a

all:	${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar rc ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all


.PHONY : all clean fclean re bonus
