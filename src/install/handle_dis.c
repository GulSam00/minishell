/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:26:04 by sham              #+#    #+#             */
/*   Updated: 2022/01/02 18:02:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

static void	ft_d_right_paste(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dis->value = temp;
}

static void	ft_d_right_append(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dis->value = temp;
}

static void	ft_d_left_normal(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_RDONLY);
	dis->value = temp;
}

int	handle_dis(t_cmd *cmd)
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
			ft_d_left_normal(dis->file_name, dis);
		else if (dis->type == OUT)
			ft_d_right_paste(dis->file_name, dis);
		else
			ft_d_right_append(dis->file_name, dis);
		cur_dis = cur_dis->next;
	}
	return (0);
}
