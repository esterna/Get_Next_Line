NAME = get_next_line
CFLAGS = -Wall -Wextra -Werror
DEPS = libft.a
FUNCTIONS = get_next_line.c\
		robin_main.c\
		alloc-wrap.c

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(CFLAGS) -o $@ $(FUNCTIONS) $(DEPS)

clean:

fclean: clean
	/bin/rm -f rm $(NAME)

re: fclean all
