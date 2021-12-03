/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/03 15:05:44 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execve_function(t_cmd *cmd)
{
    // 자신의 명령어에 지정된 리다이렉션을 처리한다.
    // cmd->func_type에 저장된 값이 0(내장함수)일 경우 포크를 한 번 더 써서 execve로 실행한다.

}

void execve_cmd(t_cmd *cmd, char **env, int func_type)
{
    pid_t pid;
    int fd[2];
    int prev_input;
        
    // $PATH
    // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
    // : 를 기준으로 나눠서 검증해야 한다.
    while (cmd)
    {
        pid = fork();
        pipe(fd);
        if (pid == 0)
        {
            // 자식 코드
            // prev, next를 검사해서 파이프를 연결한다.
       
            if (cmd->prev == NULL)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            else if (cmd->next == NULL)
            {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
            }
            else
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            execve_function(cmd); 
        }
        cmd = cmd->next;
        exit(0); 
    }
  
    return ;
}