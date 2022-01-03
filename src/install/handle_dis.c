/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:26:04 by sham              #+#    #+#             */
/*   Updated: 2022/01/03 14:38:59 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

static int	ft_d_right_paste(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp == -1)
		return (-1);
	dis->value = temp;
	return (0);
}

static int	ft_d_right_append(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp == -1)
		return (-1);
	dis->value = temp;
	return (0);
}

static int	ft_d_left_normal(char *dst, t_discriptor *dis)
{
	int	temp;

	temp = open(dst, O_RDONLY);
	if (temp == -1)
		return (-1);
	dis->value = temp;
	return (0);
}

static int	route_dis(t_discriptor *dis)
{
	if (dis->type == IN)
		return (ft_d_left_normal(dis->file_name, dis));
	else if (dis->type == OUT)
		return (ft_d_right_paste(dis->file_name, dis));
	else if (dis->type == DOUBLE_IN)
		return (ft_d_left_heredoc(dis->file_name, dis));
	else
		return (ft_d_right_append(dis->file_name, dis));
}

int	handle_dis(t_cmd *cmd)
{
	t_list			*dis_list;
	t_data			*cur_dis;
	t_discriptor	*dis;
	int				result;

	dis_list = &cmd->discriptor;
	cur_dis = dis_list->front;
	while (cur_dis)
	{
		dis = cur_dis->contents;
		result = route_dis(dis);
		if (result < 0)
		{
			if (result == -1)
				ft_error_sing_dot(dis->file_name, \
				NULL, "No such file or directory");
			return (-1);
		}
		cur_dis = cur_dis->next;
	}
	return (0);
}
