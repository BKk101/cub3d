# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bk <bk@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 16:42:20 by bykim             #+#    #+#              #
#    Updated: 2020/07/30 02:41:13 by bk               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Wall -Wextra -Werror

NAME=libft.a
HEADER=libft.h
BSRCS=$(wildcard *lst*.c)
SRCS=$(filter-out $(BSRCS), $(wildcard *.c))
OBJS=$(SRCS:.c=.o)
BOBJS=$(BSRCS:.c=.o)

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<

$(NAME) : $(OBJS)
	ar -rc $@ $(OBJS)

bonus : $(OBJS) $(BOBJS)
	ar -rc $(NAME) $^

clean :
	rm -f $(OBJS) $(BOBJS)

fclean :
	rm -f $(NAME)

re : fclean all