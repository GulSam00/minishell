/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 16:13:11 by sham             ###   ########.fr       */
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

#define FAIL -1

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_cmd
{
    char *cmd;  // 명령어. pwd, cat 같은 내장 함수일 수도 있고 echo같은 우리가 구현한 builtin 일수도 있다.
    char **arg; // 마지막 array 다음에는 NULL이 들어있어야 함.
    char *discriptor[2];
} t_cmd;

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

char *get_next_line(void);
size_t ft_strlen(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(const char *str, ssize_t offst);

int ft_getlen(char *str);
char *ft_cpstr(char *str);
int ft_cmpstr(char *str1, char *str2);
char **parse(int argc, char *argv[]);

#endif
