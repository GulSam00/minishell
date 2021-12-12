/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:56:01 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 14:46:43 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int free_str_list(t_list *list)
{
	t_data *now;
	t_data *next;

	if (list == 0)
		return (-1);
	if (list->size == 0 || list->front == 0)
		return (0);
	now = list->front;
	while (now != 0)
	{
		next = now->next;
		free(now->contents);
		free(now);
		now = next;
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void print_str_list(t_list *list)
{
	t_data *now;
	char *target;
	int index;

	if (list == 0)
	{
		printf("NULL LIST\n");
		return;
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
