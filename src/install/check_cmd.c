/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:14:06 by sham              #+#    #+#             */
/*   Updated: 2021/12/08 11:35:01 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_cmd(t_cmd *cmd, t_env *ft_env)
{
    struct stat sb;
    int i;
    int result;
    char *built_in_list[7] = [ "cd", "echo", "env", "exit", "export", "pwd", "unset" ];
    // 빌트인 함수인지를 검증한다.
    i = 0;
    while (i < 7)
    {
        result = ft_cmpstr(cmd->cmd[0], built_in_list[i]);
        if (!result)
            return (i + 1);
        i++;
    }
    // 빌드인 함수의 리스트와 하나도 일치하지 않는다.
    // 내장 명령어를 검증한다.
    // 내장 명령어가 절대 주소인지, 상대 주소인지를 모두 고려해야만 한다.
    // $PATH
    // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
    // : 를 기준으로 나눠서 검증해야 한다.
    return (stat(cmd->arg[0], &sb));
}
