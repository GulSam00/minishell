/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 14:44:16 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define MAX_PATH 4096

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#ifndef OPEN_MAX
#define OPEN_MAX 10240
#endif

#ifndef PIPE_NO
#define PIPE_READ 0
#define PIPE_WRITE 1
#endif

#include <readline/readline.h> // 프롬프트 헤더
#include <readline/history.h>  // 프롬프트 헤더
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h> // 터미널 헤더

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

// enum e_bulit_in_code
// {
// 	CD = 1,
// 	ECHO,
// 	ENV,
// 	EXIT,
// 	EXPORT,
// 	PWD,
// 	UNSET
// };

struct s_data // 디스크립터, 명령어
{
	void *contents;
	struct s_data *next;
} typedef t_data;

struct s_list
{
	void *front;
	int size;
} typedef t_list;

struct s_cmd
{
	char *cmd;	// 명령어(커맨드)
	char **arg; // 프롬프트에 입력한 문자열?
	struct s_list arg_list;
} typedef t_cmd;

struct s_env
{
	char *key;
	char *value;
} typedef t_env;

/* list */
void init_list(t_list *list);
void init_cmd(t_cmd *cmd);
int add_list(t_list *list, t_data *new_data);
int add_data(t_list *list, void *new_contents);
int free_cmd_list(t_list *list);
int free_str_list(t_list *list);
void print_cmd_list(t_list *list);
void print_str_list(t_list *list);
void print_env_list(t_list *list);
void pop_env_with_key(t_list *list, char *key);
void init_env(t_env *env, char *key, char *value);
int free_env_list(t_list *list);
int ft_parser(t_list *cmd_list, char *input);

/* libft */
char *ft_strdup(const char *str);
char *ft_strndup(const char *str, int size);
char *ft_strjoin(const char *str1, const char *str2);
int ft_strlen(const char *str);
int ft_strncmp(const char *str1, const char *str2, int len);

#endif
