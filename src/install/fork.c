/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:56:29 by sham              #+#    #+#             */
/*   Updated: 2021/12/20 19:35:09 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int sc;

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

static void single_cmd(t_data *data, t_list *env_list, int status)
{
    pid_t pid;
    t_cmd *cmd;

  cmd = data->contents;
    if (!check_bulit_in(cmd)) // 빌트인일 경우 종료 상태 수정.
    {
        execve_cmd_bult_in(cmd->arg[0], cmd, env_list, 0);
    }
    else {           
        pid = fork();
        if (pid == 0)
            execve_cmd(cmd, env_list);
        else
        {
            waitpid(pid, &status, 0);
            // printf("%d\n", WEXITSTATUS(status));
            sc = WEXITSTATUS(status);
        }
    }
}

static void multi_cmd(t_data *data,  t_list *env_list, int status)
{
    pid_t pid;
    t_cmd *cmd;
    int fd[2];
    int prev_input;

    prev_input = -1;
    while (data)
    {
        cmd = data->contents;
        pipe(fd);
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
    waitpid(pid, &status, 0);

    // printf("%d\n", WEXITSTATUS(status));
    sc = WEXITSTATUS(status);
}

void fork_cmd(t_list *cmd_list, t_list *env_list)
{
    int status;
    // t_data *data;

    signal(SIGINT, SIG_IGN); // CTRL + /
    status = 0;
    // data = cmd_list->front;
    if (cmd_list->size == 1)
      single_cmd(cmd_list->front, env_list, status);
    else
        multi_cmd(cmd_list->front, env_list, status);
    signal(SIGINT, main_sig_handler); // CTRL + C
    return;
}