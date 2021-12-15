/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:56:29 by sham              #+#    #+#             */
/*   Updated: 2021/12/15 17:03:51 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pid_child(int prev_input, int *fd, t_data *data)
{
    // 자식 코드
    // prev, next를 검사해서 파이프를 연결한다
    if (prev_input == -1)
    {
        close(fd[0]); // 출력 파이프, 첫번째는 받을 입력이 없다.
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    else if (data->next == NULL)
    {
        ft_error("마지막 파이프!\n");
        close(fd[1]); // 입력 파이프, 마지막은 넣어줄 파이프가 없다.
        dup2(prev_input, STDIN_FILENO);
        close(prev_input);
    }
    else
    {
        dup2(prev_input, STDIN_FILENO);
        close(prev_input);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
}
void fork_cmd(t_list *cmd_list, t_list *env_list)
{
    pid_t pid;
    int fd[2];
    int prev_input;
    int pid_result;
    t_data *data;
    t_cmd *cmd;

    prev_input = -1;
    data = cmd_list->front;

    if (cmd_list->size == 1)
    {
        cmd = data->contents;
        if (check_bulit_in(cmd, env_list))
        {
    pid = fork();
        if (pid == 0)
            execve_cmd(cmd, env_list);
        else 
            waitpid(pid, &pid_result, 0);
        }
    

    }
    else
    {
        while (data)
        {
            cmd = data->contents;
            pipe(fd);
          
            // printf ("%d %d\n", fd[0], fd[1]);
            pid = fork();
            if (pid == 0)
            {
                pid_child(prev_input, fd, data);
                execve_cmd(cmd, env_list);
            }
            data = data->next;
            close(fd[1]);
            if (prev_input != -1)
                close(prev_input);
            prev_input = fd[0];
        }
            close(prev_input);
            waitpid(pid, &pid_result, 0);

    }
    return;
}