/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:56:24 by sham              #+#    #+#             */
/*   Updated: 2021/12/03 15:08:04 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int prase_cmd(t_cmd *cmd, t_env *ft_env)
{
    int result;
    pid_t pid;
    t_cmd *temp;
    
    temp = cmd;
    while (cmd)
    {
        result = check_cmd(cmd, ft_env);
        cmd->func_type = result;
        if (result == -1)
        {
            ft_error_message("존재하지 않는 함수!\n");
            exit(-1);
        }
        // 0 : 내장 함수, 1 : 빌트인 함수
        cmd = cmd->next;
    }
    // init_cmd(cmd); // fd에 파이프를 지정한다. execve_cmd에서 지정한 파이프대로 dup2를 통해 연결한다.

    // 최종적인 디스크립터가 fd[2]에 담겨있다. 밑의 함수에서 실제로 dup2를 통해 세팅하게 된다. 
    execve_cmd(temp, ft_env, result);
    if (result == -1)
    {
        ft_error_message("포크 뜨기 실패!\n");
        exit(-1);
    }
    return (0);
}