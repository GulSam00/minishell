/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:10:18 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 16:36:28 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env *env, char *key, char *value)
{
	env->key = key;
	env->value = value;
}

char	*get_value(t_list *list, char *find_key)
{
	t_data *now;
	t_env *target;
	int	key_len;
	int	now_key_len;

	if (list == 0)
		return (0);
	now = list->front;
	key_len = ft_strlen(find_key);
	while (now != 0)
	{
		target = now->contents;
		now_key_len = ft_strlen(target->key);
		if (now_key_len == key_len)
		{
			if (ft_strncmp(target->key, find_key, key_len) == 0)
				return (target->value);
		}
		now = now->next;
	}
	return (0);
}

void	pop_env_with_key(t_list *list, char *key)
{
	t_data *now;
	t_data *pre;
	t_env *target;
	int	key_len;
	int	now_key_len;

	if (list == 0)
		return ;
	now = list->front;
	pre = 0;
	key_len = ft_strlen(key);
	while (now != 0)
	{
		target = now->contents;
		now_key_len = ft_strlen(target->key);
		if ((key_len == now_key_len) && (ft_strncmp(key, target->key, key_len)))
		{
			if (pre == 0)
			{
				list->front = now->next;
				free(target->key);
				free(target->value);
				free(now);
			}
			else
			{
				pre->next = now->next;
				free(target->key);
				free(target->value);
				free(now);
			}
			list->size--;
			break ;
		}
		pre = now;
		now = now->next;
	}
}

int	free_env_list(t_list *list)
{
	t_data *now;
	t_data *next;
	t_env *target;
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
		free(target->key);
		free(target->value);
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

void print_env_list(t_list *list)
{
	t_data *now;
	t_env *target;

	if (list == 0)
	{
		printf("NULL LIST\n");
		return ;
	}
	now = list->front;
	printf("\n=====PRINT ENV LIST / SIZE: %d===\n", list->size);
	while (now != 0)
	{
		target = now->contents;
		printf("key: %s | value: %s\n", target->key, target->value);
		now = now->next;
	}
	printf("=====PRINT ENV LIST END===\n");
}
