/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:13:18 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 21:34:54 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_data(t_list *list, void *new_contents)
{
	t_data *new_data;

	new_data = (t_data *)malloc(sizeof(t_data));
	if (new_data == 0)
	{
		return (-1);
	}
	new_data->contents = new_contents;
	new_data->next = 0;
	return (add_list(list, new_data));
}

int add_list(t_list *list, t_data *new_data)
{
	t_data *temp = 0;

	if (new_data == 0 || list == 0)
		return (-1);
	if (list->size == 0)
	{
		list->front = new_data;
		list->size = 1;
	}
	else
	{
		temp = list->front;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_data;
		list->size++;
	}
	return (1);
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

int	free_str_list(t_list *list)
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
