
CC=gcc
CFLAGS= -Wall -Werror -Wextra
LINK= -lft -lgnl -lmlx -framework OpenGL -framework AppKit -L./minilibx -L./libft -L./gnl
NAME=cub3d.out
SRCS=$(wildcard *.c)
LIB=$(wildcard *.a)

all : $(NAME)

$(NAME) :
	make -C libft
	make -C gnl
	make -C minilibx
	$(CC) -g $(SRCS) $(LINK) -o $@
clean :
	rm -f $(OBJS)
	make clean -C minilibx
	make clean -C libft
	make clean -C gnl
fclean : clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C gnl
re : fclean all

bonus :