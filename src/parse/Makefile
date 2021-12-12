# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/12/06 10:46:44 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = parse
CC = gcc
# CFLAGS = -lreadline
MAIN_SRCS = $(addprefix ../libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c) ft_cmd_list.c ft_list.c ft_parser.c ft_string_list.c
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