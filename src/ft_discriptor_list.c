/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_discriptor_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 13:56:39 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 14:24:34 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_discriptor(t_discriptor *discriptor, char *file_name, enum e_discriptor_type type)
{
	discriptor->file_name = file_name;
	discriptor.type = type;
}

int	free_discriptor_list(t_list *list)
{
	t_data *now;
	t_data *next;
	t_discriptor *target;
	t_data *temp;

	if (list == 0)
		return (-1);
	if (list->size == 0 || list->front == 0)
		return (0);
	now = list->front;
	while (now != 0)
	{
		next = now->next;
		target = now->contents;
		free(target->file_name);
		//free
		temp = now;
		now = next;
		free(temp);
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void print_discriptor_list(t_list *list)
{
	t_data *now;
	t_discriptor *target;

	if (list == 0)
	{
		printf("NULL LIST\n");
		return ;
	}
	now = list->front;
	printf("\n=====PRINT DISCRIPTOR LIST / SIZE: %d===\n", list->size);
	while (now != 0)
	{
		target = now->contents;
		printf("file name: %s | type: %d\n", target->file_name, target->type);
		now = now->next;
	}
	printf("=====PRINT DISCRIPTOR LIST END===\n");
}
