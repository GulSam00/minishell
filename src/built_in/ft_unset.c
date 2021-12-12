/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:29:56 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:31:16 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_env_list *env_list, char *key)
{
    t_env *now;
    t_env *pre;
    int key_len;
    int env_key_len;

    if (env_list == 0)
        return;
    now = env_list->front;
    pre = 0;
    key_len = ft_strlen(key);
    while (now != 0)
    {
        env_key_len = ft_strlen(now->key);
        if ((env_key_len == key_len) && ft_strncmp(now->key, key, key_len))
        {
            if (pre == 0)
            {
                env_list->front = now->next;
                free(now->key);
                free(now->value);
            }
            else
            {
                pre->next = now->next;
                free(now->key);
                free(now->value);
                now = pre->next;
            }
            env_list->size--;
            return;
        }
        else
        {
            pre = now;
            now = now->next;
        }
    }
}
