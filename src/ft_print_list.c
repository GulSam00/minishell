/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:31:09 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 21:31:58 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void print_str_list(t_list *list)
{
	t_data *now;
	char *target;
	int index;

	if (list == 0)
	{
		printf("NULL LIST\n");
		return ;
	}
	index = 0;
	now = list->front;
	printf("\n---PRINT STR LIST / SIZE: %d---\n", list->size);
	while (now != 0)
	{
		target = now->contents;
		printf("[%d] %s\n", index, target);
		now = now->next;
		index++;
	}
	printf("---PRINT STR LIST END---\n");
}

