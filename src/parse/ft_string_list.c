/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:39 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:52:41 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_str_list(t_list *list)
{
	t_data	*now;
	t_data	*next;

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

void	print_str_list(t_list *list)
{
	t_data	*now;
	char	*target;
	int		index;

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
