/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 16:50:47 by sham             ###   ########.fr       */
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

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// STDIN_FILENO 0
// STDOUT_FILENO 1
// STDERR_FILENO 2

typedef struct s_cmd
{
    char **arg;  // 명령어. pwd, cat 같은 내장 함수일 수도 있고 echo같은 우리가 구현한 builtin 일수도 있다. execve로 실행할 때 배열의 첫번째에 명령어를 넣어야 하기 때문에 cmd[0] = "cat", "pwd"가 들어가게 된다.
    struct s_dis *dis;
    int fd[2];
    struct s_cmd *next;
} t_cmd;

typedef struct s_dis
{
    char *type; // <, <<, >, >>
    char *dst;
    struct s_dis *next;
} t_dis;


typedef struct s_env
{
    char *env; // env 시 나오는 명령어를 개행을 기준으로 나눠
    struct s_dis *next;
} t_env;

char *get_next_line(void);
size_t ft_strlen(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(const char *str, ssize_t offst);

int ft_getlen(char *str);
char *ft_cpstr(char *str);
int ft_cmpstr(char *str1, char *str2);
int ft_error_message(char *message);
char **parse(int argc, char *argv[]);

#endif
