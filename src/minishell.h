/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 17:36:41 by sham             ###   ########.fr       */
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

#include <sys/types.h> // stat 헤더
#include <sys/stat.h>  // stat 헤더

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
} typedef t_data;

struct s_list
{
	void *front;
	int size;
} typedef t_list;

struct s_cmd
{
	char *cmd;
	char **arg;
	struct s_list arg_list;
	struct s_list discriptor;
} typedef t_cmd;

struct s_env
{
	char *key;
	char *value;
} typedef t_env;
struct s_discriptor
{
	char *file_name;
	enum e_discriptor_type type;
} typedef t_discriptor;

/* list */
void init_list(t_list *list);
void init_cmd(t_cmd *cmd);
int add_data(t_list *list, void *new_contents);
int free_cmd_list(t_list *list);
int free_str_list(t_list *list);
void print_cmd_list(t_list *list);
void print_str_list(t_list *list);
void print_env_list(t_list *list);
void pop_env_with_key(t_list *list, char *key);
void init_env(t_env *env, char *key, char *value);
char *get_value(t_list *list, char *find_key);
int free_env_list(t_list *list);
void init_discriptor(t_discriptor *discriptor, char *file_name, enum e_discriptor_type type);
int free_discriptor_list(t_list *list);
void print_discriptor_list(t_list *list);

int ft_parser(t_list *cmd_list, char *input);
int ft_env_parser(t_list *env_list, char **envp);
enum e_cmd_type get_type(char *word);

/* libft */
char *ft_strdup(const char *str);
char *ft_strndup(const char *str, int size);
char *ft_strjoin(const char *str1, const char *str2);
char *ft_strjoin_path(const char *str1, const char *str2);
int ft_strlen(const char *str);
int ft_strncmp(const char *str1, const char *str2, int len);
int ft_cmpstr(char *str1, char *str2);
char **ft_split(char const *s, char c);
size_t ft_strlcpy(char *destination, const char *source, size_t n);

/* install */
void fork_cmd(t_list *cmd_list, t_list *env_list);
int check_cmd(t_cmd *cmd, t_list *env_list);
int check_bulit_in(t_cmd *cmd, t_list *env_list);

#endif
