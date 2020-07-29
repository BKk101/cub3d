
CC=gcc
CFLAGS= -Wall -Werror -Wextra
LINK= -lmlx -framework OpenGL -framework AppKit -L./minilibx
NAME=cub3d.out
SRCS=$(wildcard *.c)

all : $(NAME)

$(NAME) :
	make -C minilibx
	$(CC) $(SRCS) $(LINK) -o $@
clean :
	rm -f $(OBJS)
	make clean -C minilibx

fclean : clean
	rm -f $(NAME)

re : fclean all

bonus :