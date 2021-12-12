/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:14:06 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 16:25:41 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char **environ;

int check_cmd(t_cmd *cmd, t_env *ft_env)
{
    if (ft_env)
    {
        printf("env\n");
    }
    struct stat sb;
    int i;
    int result;
    char **path;
    char *built_in_list[7] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    // 빌트인 함수인지를 검증한다.
    i = 0;
    while (i < 7)
    {
        result = ft_cmpstr(cmd->arg[0], built_in_list[i]);
        if (!result)
            return (i + 1);
        i++;
    }
    printf("%s\n", environ[1]);
    path = ft_strdup(&environ[1][5]);
    printf("%s\n", path);

    printf("검사할 문자열 : %s\n", cmd->arg[0]);
    // 빌드인 함수의 리스트와 하나도 일치하지 않는다.
    // 내장 명령어를 검증한다.
    // 내장 명령어가 절대 주소인지, 상대 주소인지를 모두 고려해야만 한다.
    // 이차원 배열로 들어올 것.
    result = stat(cmd->arg[0], &sb);
    if (result)
    {
        while (path) // 이차원 배열이나 연결리스트
        {
            result = stat(ft_strjoin_path(*path, cmd->arg[0]), &sb);
            if (!result)
                return (0);
            path++;
        }
    }

    // $PATH
    // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
    // : 를 기준으로 나눠서 검증해야 한다.
    return (-1);
}
