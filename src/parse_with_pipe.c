/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_with_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:56:24 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 17:57:35 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int prase_with_pipe(t_cmd *cmd, t_env *ft_env)
{
    int code;
    pid_t pid;

    // 마지막부터 실행해야 하기 때문에 재귀로 마지막 명령어부터 실행한다.
    // 명령어의 다음에 

    code = check_vaild(cmd, ft_env);
    if (code == -1)
    {
        ft_error_message("존재하지 않는 함수!\n");
        exit(-1);
    }
    // 0 : 내장 함수, 1 : 빌트인 함수
    else
    {
        // 파이프 이곳에서 만들기?
        init_descriptor(cmd->dis);
        // 빌트인 함수 여도 디스크립터가 세팅된 뒤에야 실행 가능.
        execve_function(cmd->cmd);
    }
 
    return (0);
}