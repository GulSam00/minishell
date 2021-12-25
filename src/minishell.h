/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 18:17:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define MAX_PATH 4096
#define OPEN_MAX 10240
#define PIPE_READ 0
#define PIPE_WRITE 1
#define LLONG_MIN -9223372036854775808
#define LONG1_MAX (long long)9223372036854775807

#include <stdio.h>			   // <readline/readline.h>보다 먼저 선언되야 함.
#include <readline/readline.h> // 프롬프트 헤더
#include <readline/history.h>  // 프롬프트 헤더
#include <stdlib.h>			   // malloc
#include <unistd.h>			   // write
#include <fcntl.h>
#include <termios.h> // 터미널 헤더

#include <sys/types.h> // stat 헤더
#include <sys/stat.h>  // stat 헤더
#include <string.h>	   // strerror
#include <errno.h>	   // errno 에러 전역 변수
#include <signal.h>
#include <limits.h> // exit 최소값 처리

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
	IN,		   // <, 0
	OUT,	   // >, 1
	DOUBLE_IN, // <<, 2
	DOUBLE_OUT // >>, 3
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

struct heredoc_list
{
	char *str;
	struct heredoc_list *next;
} typedef t_h_list;
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
char **env_to_char(t_list *env_list);
void init_discriptor(t_discriptor *discriptor, char *file_name, enum e_discriptor_type type);
int free_discriptor_list(t_list *list);
void print_discriptor_list(t_list *list);
enum e_discriptor_type get_discriptor_type(char *word);
int ft_parser(t_list *cmd_list, char *input, t_list *env_list);
int ft_env_parser(t_list *env_list, char **envp);
enum e_cmd_type get_type(char *word);

char *ft_quotes(char *str, t_list *env_list, int first_quotes);
int ft_div_input(t_list *word_list, char *input, t_list *env_list);
/* libft */
char *ft_strdup(const char *str);
char *ft_strndup(const char *str, int size);
char *ft_strjoin(const char *str1, const char *str2);
char *ft_strjoin_path(const char *str1, const char *str2);
char *ft_strjoin_with_char(const char *str1, const char *str2, const char c);
int ft_strlen(const char *str);
int ft_strncmp(const char *str1, const char *str2, int len);
int ft_cmpstr(char *str1, char *str2);
char **ft_split(char const *s, char c);
size_t ft_strlcpy(char *destination, const char *source, size_t n);
char	*ft_itoa(long n);

/* install */
void	fork_cmd(t_list *cmd_list, t_list *env_list);
int 	handle_dis(t_cmd *cmd);
int		check_bulit_in(t_cmd *cmd);
void	parse_cmd(t_cmd *cmd, t_list *env_list);
void	execve_cmd_bult_in(char *cmd_name, t_cmd *cmd, t_list *env_list, int is_forked);
void	execve_cmd_normal(char *cmd_name, t_cmd *cmd, t_list *env_list);

/* bulit_in */
int ft_cd(char *path, t_list *env_list);
int ft_pwd(void);
int ft_echo(char *argv[]);
int ft_exit(char *argv[], int is_forked);

/* error */
void ft_error(char *cmd, char *arg, char *message);

/* signal */
void main_sig_handler(int signal);
void heredoc_sig_handler(int signal);
void execve_sig_handler(int signal);

#endif
