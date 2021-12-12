/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:13:18 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 11:48:43 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_list *list)
{
	list->front = 0;
	list->size = 0;
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
