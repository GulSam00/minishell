/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:57:01 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:50:20 by nasong           ###   ########.fr       */
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

void	free_cmd(t_cmd *target)
{
	int	index;

	index = 0;
	free_str_list(&target->arg_list);
	free_discriptor_list(&target->discriptor);
	free(target->cmd);
	while (target->arg[index] != 0)
		free(target->arg[index++]);
	free(target->arg);
}

int	free_cmd_list(t_list *list)
{
	t_data	*now;
	t_data	*next;
	t_cmd	*target;
	t_data	*temp;

	if (list == 0)
		return (-1);
	if (list->size == 0 || list->front == 0)
		return (0);
	now = list->front;
	while (now != 0)
	{
		next = now->next;
		target = now->contents;
		free_cmd(target);
		free(target);
		temp = now;
		now = next;
		free(temp);
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void	print_arg(char **arg)
{
	int	index;

	index = 0;
	while (arg[index] != 0)
	{
		printf("[%d] %s\n", index, arg[index]);
		index++;
	}
}

void	print_cmd_list(t_list *list)
{
	t_data	*now;
	t_cmd	*target;
	int		index;

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
		print_str_list(&target->arg_list);
		print_discriptor_list(&target->discriptor);
		now = now->next;
	}
	printf("=====PRINT CMD LIST END===\n");
}
