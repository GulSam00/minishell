/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:57:01 by nasong            #+#    #+#             */
/*   Updated: 2021/12/06 10:41:12 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = 0;
	cmd->arg = 0;
	init_list(&cmd->arg_list);	
	init_list(&cmd->discriptor);	
}

int	free_cmd_list(t_list *list)
{
	t_data *now;
	t_data *next;
	t_cmd *target;

	if (list == 0)
		return (-1);
	if (list->size == 0 || list->front == 0)
		return (0);
	now = list->front;
	while (now != 0)
	{
		next = now->next;
		target = now->contents;
		//free
		now = next;
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void print_cmd_list(t_list *list)
{
	t_data *now;
	t_cmd *target;
	int index;

	if (list == 0)
	{
		printf("NULL LIST\n");
		return ;
	}
	now = list->front;
	printf("\n=====PRINT CMD LIST / SIZE: %d===\n", list->size);
	while (now != 0)
	{
		index = 0;
		target = now->contents;
		printf("cmd: %s | arg: %s\n", target->cmd, target->arg);
		print_str_list(&target->arg_list);
		now = now->next;
	}
	printf("=====PRINT CMD LIST END===\n");
}
