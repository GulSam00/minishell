/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:26:04 by sham              #+#    #+#             */
/*   Updated: 2021/12/20 15:17:36 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO

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
    printf("%s\n", dst);
    // char *buf;
    // while (1)
    // {
    //     buf = get_next_line();
    //     if (ft_cmpstr(dst, buf) == 0)
    //         break;
    // }
    // 어캐 하냐...
    return (0);
}

int handle_dis(t_cmd *cmd)
{
    t_list *dis_list;
    t_data *cur_dis;
    t_discriptor *dis;
    dis_list = &cmd->discriptor;
    cur_dis = dis_list->front;

    // printf("dis start!\n");
    while (cur_dis)
    {
        dis = cur_dis->contents;
        // printf ("dis->type : %d\n", dis->type);
        // printf ("dis->tpye : %s\n", dis->type);
        if (dis->type == IN)
            ft_d_left_normal(dis->file_name);
        else if (dis->type == DOUBLE_IN)
            ft_d_left_heredoc(dis->file_name);
        else if (dis->type == OUT)
            ft_d_right_paste(dis->file_name);
        else if (dis->type == DOUBLE_OUT)
            ft_d_right_append(dis->file_name);
        else
            return (-1);
        cur_dis = cur_dis->next;
        // printf ("dis!\n");
    }
    // printf ("dis end!\n");
    return (0);
}
