/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:30:15 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:30:21 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_env_list *env_list, char *key, char *value)
{
    t_env *new;
    t_env *now;

    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = 0;
    now = env_list->front;
    if (now == 0)
    {
        env_list->front = new;
        env_list->size = 1;
    }
    else
    {
        while (now->next != 0)
        {
            now = now->next;
        }
        now->next = new;
        env_list->size++;
    }
}
