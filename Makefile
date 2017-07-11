NAME = get_next_line
CFLAGS = -Wall -Wextra -Werror -g
DEPS = libft.a
FUNCTIONS = ~/Projects/Get_Next_Line/Get_Next_Line_2/testing/get_next_line.c\
			main.c

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(CFLAGS) -o $@ $(FUNCTIONS) $(DEPS)

clean:

fclean: clean
	/bin/rm -f rm $(NAME)

re: fclean all
