NAME = get_next_line
CFLAGS = -Wall -Wextra -Werror
FUNCTIONS = $(wildcard *.c)

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(CFLAGS) -o $@ $(FUNCTIONS)

clean:

fclean: clean
	/bin/rm -f rm $(NAME)

re: fclean all
