
CC=gcc
CFLAGS= -Wall -Werror -Wextra
LINK= -lmlx -framework OpenGL -framework AppKit
NAME=cub3d.out
SRCS=$(wildcard *.c)

all : $(NAME)

$(NAME) : 
	$(CC) $(SRCS) $(LINK) -o $@
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

bonus :