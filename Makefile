# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/12/08 21:36:57 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = nanoshell
CC = gcc -Werror -Wall -Wextra
FLAG = -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include
# READLINE = -Werror -Wall -Wextra -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include
MAIN_SRCS = $(addprefix src/, temp.c)
SIGNAL_SRCS = testsignal.c
OBJS = $(MAIN_SRCS:.c=.o)
SIGNAL_OBJS = $(SIGNAL_SRCS:.c=.o)
.PHONY : all clean fclean re

all : $(NAME)

signal : $(SIGNAL_OBJS)
	$(CC) $(FLAG) $(SIGNAL_OBJS) -o signal


$(NAME) : $(MAIN_SRCS)
	$(CC) $(OBJS) -o $(NAME) 

clean :
	rm -rf $(OBJS) $(SIGNAL_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean signal