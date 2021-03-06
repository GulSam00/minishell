/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_discriptor_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:51:26 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:51:28 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_discriptor(t_discriptor *discriptor, \
char *file_name, enum e_discriptor_type type)
{
	discriptor->file_name = file_name;
	discriptor->type = type;
	discriptor->value = -1;
}

enum e_discriptor_type	get_discriptor_type(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (word[0] == '<')
	{
		if (len == 1)
			return (IN);
		return (DOUBLE_IN);
	}
	else
	{
		if (len == 1)
			return (OUT);
		return (DOUBLE_OUT);
	}
}

int	free_discriptor_list(t_list *list)
{
	t_data			*now;
	t_data			*next;
	t_discriptor	*target;
	t_data			*temp;

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
		temp = now;
		now = next;
		free(temp);
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void	print_discriptor_list(t_list *list)
{
	t_data			*now;
	t_discriptor	*target;

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
