# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 16:48:56 by sham              #+#    #+#              #
#    Updated: 2022/01/03 14:34:33 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 
LINKING_FLAGS = -lreadline ${LDFLAGS}
COMFILE_FLAGS = ${CPPFLAGS}
MAIN_SRCS =  $(addprefix src/, main.c)
INSTALL_SRCS = $(addprefix src/install/, check_cmd.c execve_cmd.c fork_cmd.c fork_cmd_multi.c handle_dis.c heredoc.c set_dis.c)
PARSE_SRCS = $(addprefix src/parse/, ft_cmd_list.c ft_list.c ft_env_list.c ft_parser.c ft_string_list.c ft_check_type.c ft_env_parser.c ft_discriptor_list.c ft_div_input.c ft_to_char.c ft_check_quotes.c ft_get_word.c ft_change.c)
LIBFT_SRCS = $(addprefix src/libft/, ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_cmpstr.c ft_split.c ft_strlcpy.c ft_itoa.c ft_isdigit.c)
BUILT_IN_SRCS = $(addprefix src/built_in/, ft_cd.c ft_pwd.c ft_echo.c ft_exit.c ft_env.c ft_export.c ft_unset.c)
ERROR_SRCS = $(addprefix src/error/, ft_error.c )
SINGAL_SRCS = $(addprefix src/signal/, signal_handler.c )

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
INSTALL_OBJS = $(INSTALL_SRCS:.c=.o)
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
BUILT_IN_OBJS = $(BUILT_IN_SRCS:.c=.o) 
ERROR_OBJS = $(ERROR_SRCS:.c=.o) 
SINGAL_OBJS = $(SINGAL_SRCS:.c=.o) 

all : $(NAME)



$(NAME) : $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS) $(INSTALL_OBJS) $(BUILT_IN_OBJS) $(ERROR_OBJS) $(SINGAL_OBJS)
	$(CC) $(CFLAGS) $(LINKING_FLAGS) $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS) $(INSTALL_OBJS) $(BUILT_IN_OBJS) $(ERROR_OBJS) $(SINGAL_OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@

clean :
	rm -rf $(MAIN_OBJS) $(LIBFT_OBJS) $(PARSE_OBJS) $(INSTALL_OBJS) $(BUILT_IN_OBJS) $(ERROR_OBJS) $(SINGAL_OBJS) 

fclean : clean
	rm -rf $(NAME)

re : fclean all


.PHONY : all clean fclean re
