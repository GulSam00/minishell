# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/11/28 16:18:44 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = nanoshell
CC = gcc
CFLAGS = -lreadline
MAIN_SRCS = $(addprefix src/, descriptor.c util.c get_next_line.c get_next_line_utils.c)
OBJS = $(MAIN_SRCS:.c=.o)		

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean :
	rm -rf $(OBJS) 

fclean : clean
	rm -rf $(NAME)

re : fclean all