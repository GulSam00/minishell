/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vaild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:14:06 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 17:54:04 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_vaild(t_cmd *cmd, t_env *ft_env)
{
    struct stat sb;
    int is_vaild;
    // 빌트인 함수인지를 검증한다.
    is_vaild = -1;
    is_vaild *= ft_cmpstr(cmd->cmd[0], "cd");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "echo");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "env");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "exit");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "export");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "pwd");
    is_vaild *= ft_cmpstr(cmd->cmd[0], "unset");
    if (!is_vaild)
        return (1);
    // 빌드인 함수의 리스트와 하나도 일치하지 않는다.
    // 내장 명령어를 검증한다.
    // 내장 명령어가 절대 주소인지, 상대 주소인지를 모두 고려해야만 한다.
    // 명령어를 합치는 것을 여기서 하나?
    return (stat(cmd->arg[0], &sb));
}

int is_vaild_function(t_cmd *cmd, t_env *ft_env)
{
    int code;
    int fd[2];
    int i;

    i = 0;
    // 마지막부터 실행해야 하기 때문에 재귀로 마지막 명령어부터 실행한다.
    // 명령어의 다음에 

    while (cmd)
    {
    code = check_vaild(cmd, ft_env);
    if (cmd->next)
    {
        // 파이프 뜨고 앞에 명령어가 있다면 쓰기 파이프 fd[1] 값 전달
        // 이전에 명령어가 있었다면 읽기 파이프 fd[0] 값 전달

        pipe(fd);
        pipe_connect(cmd, fd, i);
    }
    if (code == -1)
    {
        ft_error_message("존재하지 않는 함수!\n");
        exit(-1);
    }       
        if (code == 0)
        {
            install_function(cmd);
        }
        if (code == 1)
        // 파이프 이곳에서 만들기?
        // 빌트인 함수 여도 디스크립터가 세팅된 뒤에야 실행 가능.
        execve_function(cmd);
        cmd = cmd->next;
        i++;
    }

    return (0);
}