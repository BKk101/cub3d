
CC=gcc
CFLAGS= -Wall -Werror -Wextra
LINK= -lft -lgnl -lmlx -framework OpenGL -framework AppKit -L./libft -L./gnl -L../minilibx
INCLUDES = -I ./cub3d.h
NAME=cub3D
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIB=$(wildcard *.a)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	make -C gnl
	$(CC) $(CFLAGS) $(LINK) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	rm -f $(OBJS)
	make clean -C libft
	make clean -C gnl

fclean : clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C gnl

re : fclean all

bonus : all