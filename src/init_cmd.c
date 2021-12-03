/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:26:04 by sham              #+#    #+#             */
/*   Updated: 2021/12/03 13:51:25 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO
extern char **environ;

int ft_d_right_paste(char *dst)
{
    int temp;
    temp = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp == -1)
        return (-1);

    if (dup2(temp, STDOUT_FILENO) == -1) // 에러?
        return (-1);
    return (close(temp));
}

int ft_d_right_append(char *dst)
{
    int temp;

    temp = open(dst, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (temp == -1)
        return (-1);
    if (dup2(temp, STDOUT_FILENO) == -1)
        return (-1);
    return (close(temp));
}

int ft_d_left_normal(char *dst)
{
    int temp;
    temp = open(dst, O_RDONLY);
    if (dup2(temp, STDIN_FILENO) == -1)
        return (-1);
    return (close(temp));
}

int ft_d_left_heredoc(char *dst)
{
    char *buf;
    while (1)
    {
        buf = get_next_line();
        if (ft_cmpstr(dst, buf) == 0)
            break;
    }
    return (0);
}

int init_dis(t_dis *dis)
{
    while (dis)
    {
        if (!ft_cmpstr(dis->type, ">"))
            ft_d_right_paste(dis->dst);
        else if (!ft_cmpstr(dis->type, ">>"))
            ft_d_right_append(dis->dst);
        else if (!ft_cmpstr(dis->type, "<"))
            ft_d_left_normal(dis->dst);
        else if (!ft_cmpstr(dis->type, "<<"))
            ft_d_left_heredoc(dis->dst);
        else
    {
        ft_error_message("no match!\n");
        return (-1);
    }
    dis = dis->next;
    }

    return (0);
}

// int init_cmd(t_cmd *cmd)
// {
//     int fd[2];
//     int prev_input;
    
//     while (cmd->next)
//     {
//         pipe(fd);
//         if (cmd->prev == NULL)
//         {
//             cmd->fd[0] = -1;
//             cmd->fd[1] = fd[1];
//         }
//         else
//         {
//             cmd->fd[0] = prev_input;
//             cmd->fd[1] = fd[1];
//         }
//         prev_input = fd[0];
//         cmd = cmd->next;
//     }
// }