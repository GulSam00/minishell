# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/12/12 16:11:38 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = nanoshell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 
READLINE_FLAG = -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include
# READLINE = -Werror -Wall -Wextra -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include
MAIN_SRCS =  $(addprefix src/, main.c) src/install/execve.c src/install/check_cmd.c
PARSE_SRCS = $(addprefix src/parse/, ft_cmd_list.c ft_list.c ft_parser.c ft_string_list.c ft_check_type.c)
LIBFT_SRCS = $(addprefix src/libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_cmpstr.c)

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)



$(NAME) : $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAG) $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS) -o $(NAME) 


clean :
	rm -rf $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all