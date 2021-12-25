/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:10:18 by nasong            #+#    #+#             */
/*   Updated: 2021/12/25 20:54:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(t_env *env, char *key, char *value)
{
	env->key = key;
	env->value = value;
}

void	pop_env_with_key(t_list *list, char *key)
{
	t_env	*now;
	t_env	*pre;
	int		key_len;
	int		now_key_len;

	if (list == 0)
		return ;
	now = list->front;
	pre = 0;
	key_len = ft_strlen(key);
	while (now != 0)
	{
		now_key_len = ft_strlen(now->key);
		if ((key_len == now_key_len) && (ft_strncmp(key, now->key, key_len)))
		{
			if (pre == 0)
			{
				list->front = now->next;
				free(now->key);
				free(now->value);
				free(now);
			}
			else
			{
				pre->next = now->next;
				free(now->key);
				free(now->value);
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
	t_data	*now;
	t_data	*next;
	t_env	*target;

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
		now = next;
		list->size--;
	}
	list->front = 0;
	list->size = 0;
	return (1);
}

void	print_env_list(t_list *list)
{
	t_data	*now;
	t_env	*target;

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
