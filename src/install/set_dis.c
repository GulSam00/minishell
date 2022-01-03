/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:26:33 by marvin            #+#    #+#             */
/*   Updated: 2022/01/02 17:56:00 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 메인 프로세스에서 디스크립터 close
void	close_main_fd(t_cmd *cmd)
{
	t_list			*dis_list;
	t_data			*cur_dis;
	t_discriptor	*dis;

	dis_list = &cmd->discriptor;
	cur_dis = dis_list->front;
	while (cur_dis)
	{
		dis = cur_dis->contents;
		close(dis->value);
		cur_dis = cur_dis->next;
	}
}

void	dup_cmd_dis(t_cmd *cmd)
{
	t_list			*dis_list;
	t_data			*cur_dis;
	t_discriptor	*dis;

	dis_list = &cmd->discriptor;
	cur_dis = dis_list->front;
	while (cur_dis)
	{
		dis = cur_dis->contents;
		if (dis->type == IN || dis -> type == DOUBLE_IN)
		{
			dup2(dis->value, STDIN_FILENO);
			close(dis->value);
		}
		else if (dis->type == OUT || dis->type == DOUBLE_OUT)
		{
			dup2(dis->value, STDOUT_FILENO);
			close(dis->value);
		}
		cur_dis = cur_dis->next;
	}
}

int	return_out_dis(t_cmd *cmd)
{
	t_list			*dis_list;
	t_data			*cur_dis;
	t_discriptor	*dis;
	int				dis_value;

	dis_list = &cmd->discriptor;
	cur_dis = dis_list->front;
	while (cur_dis)
	{
		dis = cur_dis->contents;
		if (dis->type == OUT || dis->type == DOUBLE_OUT)
		{
			dis_value = dis->value;
		}
		cur_dis = cur_dis->next;
	}
	if (dis_value == -1)
		return (1);
	return (dis_value);
}
