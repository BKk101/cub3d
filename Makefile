
CC=gcc
CFLAGS= -Wall -Werror -Wextra
LINK= -lft -lmlx -framework OpenGL -framework AppKit -L./minilibx -L./libft
NAME=cub3d.out
SRCS=$(wildcard *.c)

all : $(NAME)

$(NAME) :
	make -C libft
	make -C minilibx
	$(CC) $(SRCS) $(LINK) -o $@
clean :
	rm -f $(OBJS)
	make clean -C minilibx
	make clean -C libft
fclean : clean
	rm -f $(NAME)

re : fclean all

bonus :