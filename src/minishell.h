/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/05 22:16:28 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define MAX_PATH 4096

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

enum e_cmd_type
{
	CMD = 0,
	ARG,
	DISCRIPTOR,
	OPTION,
	CMD_TYPE_MAX,
	PIPE
};

enum e_discriptor_type
{
	IN,
	OUT,
	DOUBLE_IN,
	DOUBLE_OUT
};

struct s_data
{
	void *contents;
	struct s_data *next;
}	typedef t_data;

struct s_list
{
	void *front;
	int size;
}	typedef t_list;

struct s_cmd
{
	char *cmd;
	char *arg;
	struct s_list arg_list;
	struct s_list discriptor;
}	typedef t_cmd;

struct s_env
{
	char *key;
	char *value;
}	typedef t_env;

void	init_list(t_list *list);
void	init_cmd(t_cmd *cmd);
int	add_list(t_list *list, t_data *new_data);
int add_data(t_list *list, void *new_contents);
int free_cmd_list (t_list *list);
int	free_str_list(t_list *list);
void print_cmd_list(t_list *list);
void print_str_list(t_list *list);

int ft_parser(t_list *cmd_list, char *input);


/* libft */
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int size);
char	*ft_strjoin(const char *str1, const char *str2);
int ft_strlen(const char *str);
int     ft_strncmp(const char *str1, const char *str2, int len);
#endif
