# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2021/12/13 13:21:01 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = nanoshell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 
COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
MAIN_SRCS =  $(addprefix src/, main.c) src/install/execve.c src/install/fork.c
PARSE_SRCS = $(addprefix src/parse/, ft_cmd_list.c ft_list.c ft_env_list.c ft_parser.c ft_string_list.c ft_check_type.c ft_env_parser.c)
LIBFT_SRCS = $(addprefix src/libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_cmpstr.c ft_split.c ft_strlcpy.c)

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)


all : $(NAME)



$(NAME) : $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS)
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean :
	rm -rf $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all


.PHONY : all clean fclean re