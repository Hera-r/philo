CC=cc
CFLAGS=-Wall -Wextra -Werror -g3 #-fsanitize=thread -g3
NAME=philo
SRC_FILES=main.c libft_tmp.c parsing.c all_init.c xdisplay.c actions.c xstart.c
OBJ_FILES=$(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
