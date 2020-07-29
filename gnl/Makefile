CC=gcc
CFLAGS= -Wall -Wextra -Werror

NAME=libgnl.a
HEADER=get_next_line.h
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -I$(HEADER)

$(NAME) : $(OBJS)
	ar -rc $@ $(OBJS)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(NAME)

re : fclean all