/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 16:59:40 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void excuve_cmd_built_in(t_cmd *cmd, t_env *ft_env, int result)
// {
//     if (ft_env)
//     {
//         printf("env\n");
//     }
//     // 공통 : 파일 디스크립터 조정
//     // 실행하고 exit으로 종료?
// }

// void excuve_cmd_normal(t_cmd *cmd, t_env *ft_env, int result)
// {
//     if (ft_env)
//     {
//         printf("env\n");
//     }

//     exit(0);
//     // 공통 : 파일 디스크립터 조정
//     // 포크 떠서 실행하고 부모 프로세스는 exit으로 종료?
// }

void excuve_cmd(t_cmd *cmd, t_list *env_list)
{
    int result;
    result = check_cmd(cmd, env_list);
    if (result == -1)
    {
        write(2, "존재하지 않는 함수!\n", 29);
        exit(-1);
    }
    printf("result : %d\n", result);
    // else if (result > 0)
    // {
    //     excuve_cmd_built_in(cmd, ft_env, result);
    // }
    // else
    // {
    //     excuve_cmd_normal(cmd, ft_env, result);
    // }
    exit(0);
}

void fork_cmd(t_list *cmd_list, t_list *env_list)
{
    pid_t pid;
    int fd[2];
    int prev_input = -1;
    t_data *data;
    t_cmd *cmd;

    t_env *temp;
    temp = NULL;

    data = cmd_list->front;
    while (data)
    {
        cmd = data->contents;
        pipe(fd);
        pid = fork();
        pipe(fd);
        if (pid == 0)
        {
            // 자식 코드
            // prev, next를 검사해서 파이프를 연결한다
            // if (prev_input == -1)
            // {
            //     close(fd[0]);
            //     dup2(fd[1], STDOUT_FILENO);
            //     close(fd[1]);
            // }
            // else if (data->next == NULL)
            // {
            //     close(fd[1]);
            //     dup2(prev_input, STDIN_FILENO);
            //     close(prev_input);
            // }
            // else
            // {
            //     dup2(prev_input, STDIN_FILENO);
            //     close(prev_input);
            //     dup2(fd[1], STDOUT_FILENO);
            //     close(fd[1]);
            // }
            excuve_cmd(cmd, env_list);
        }
        data = data->next;
        if (prev_input != -1)
            close(prev_input);
        prev_input = fd[0];
    }
    return;
}