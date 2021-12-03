/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vaild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:14:06 by sham              #+#    #+#             */
/*   Updated: 2021/12/03 13:27:26 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_cmd(t_cmd *cmd, t_env *ft_env)
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
