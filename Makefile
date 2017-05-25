NAME = get_next_line
CFLAGS = -Wall -Wextra -Werror -g
DEPS = libft.a
FUNCTIONS = gnl_real.c\
			main.c

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(CFLAGS) -o $@ $(FUNCTIONS) $(DEPS)

clean:

fclean: clean
	/bin/rm -f rm $(NAME)

re: fclean all
