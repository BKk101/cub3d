# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bk <bk@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 16:42:20 by bykim             #+#    #+#              #
#    Updated: 2020/07/30 15:59:36 by bk               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Wall -Wextra -Werror

NAME=libft.a
HEADER=libft.h
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<

$(NAME) : $(OBJS)
	ar -rc $@ $(OBJS)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(NAME)

re : fclean all