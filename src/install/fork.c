/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:56:29 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 18:38:24 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fork_cmd(t_list *cmd_list, t_list *env_list)
{
    pid_t pid;
    int fd[2];
    int prev_input = -1;
    t_data *data;

    t_cmd *cmd;

    if (cmd_list->size == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            data = cmd_list->front;
            cmd = data->contents;
            excuve_cmd(cmd, env_list);
        }
    }
    else
    {
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
                if (prev_input == -1)
                {
                    printf("첫번째!\n");
                    close(fd[0]);
                    dup2(fd[1], STDOUT_FILENO);
                    // close(fd[1]);
                }
                else if (data->next == NULL)
                {
                    printf("마지막!\n");

                    close(fd[1]);
                    dup2(prev_input, STDIN_FILENO);
                    // close(prev_input);
                }
                else
                {
                    dup2(prev_input, STDIN_FILENO);
                    close(prev_input);
                    dup2(fd[1], STDOUT_FILENO);
                    // close(fd[1]);
                }
                excuve_cmd(cmd, env_list);
            }
            data = data->next;
            if (prev_input != -1)
                close(prev_input);
            prev_input = fd[0];
        }
    }
    return;
}