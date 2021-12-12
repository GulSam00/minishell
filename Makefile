# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/12/12 14:10:37 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = nanoshell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 
FLAG = -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include
# READLINE = -Werror -Wall -Wextra -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include
MAIN_SRCS = $(addprefix src/list/, ft_cmd_list.c ft_list.c ft_parser.c ft_string_list.c) src/main.c
LIBFT_SRCS = $(addprefix src/libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c)
SIGNAL_SRCS = testsignal.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
SIGNAL_OBJS = $(SIGNAL_SRCS:.c=.o)
.PHONY : all clean fclean re

all : $(NAME)

signal : $(SIGNAL_OBJS)
	$(CC) $(CFLAGS) $(SIGNAL_OBJS) -o signal


$(NAME) : $(MAIN_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) -lreadline $(MAIN_OBJS) $(LIBFT_OBJS) -o $(NAME) 

clean :
	rm -rf $(MAIN_OBJS) $(LIBFT_OBJS) $(SIGNAL_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean signal