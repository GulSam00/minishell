/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:26:33 by marvin            #+#    #+#             */
/*   Updated: 2022/01/01 12:26:33 by marvin           ###   ########.fr       */
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
		if (dis->type == IN)
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
// 자식 프로세스에서 실행 전 입력 출력 디스크립터 세팅