CC=cc
NAME=philo
SRC_FILES=main.c
OBJ=$(SRC_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -ggdb -c $< -o $@

$(NAME): $(OBJ) my_libft/libft.a ft_printf/libftprintf.a
	$(CC) $(OBJ) -Lmy_libft -lft -Lft_printf -lftprintf -ggdb -o $(NAME)

my_libft/libft.a:
	make -C my_libft

ft_printf/libftprintf.a:
	make -C ft_printf

clean:
	rm -f $(OBJ)
	make clean -C my_libft
	make fclean -C ft_printf

fclean: clean
	rm -f $(NAME)


re: fclean all


.PHONY: all clean fclean re