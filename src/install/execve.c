/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 17:36:57 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excuve_cmd(t_cmd *cmd, t_list *env_list)
{
    int result;

    result = check_bulit_in(cmd, env_list);
    if (result == -1)
    {
        result = check_cmd(cmd, env_list);
    }
    if (result == -1)
    {
        write(2, "존재하지 않는 함수!\n", 29);
        exit(-1);
    }
    printf("함수 끝!\n");
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