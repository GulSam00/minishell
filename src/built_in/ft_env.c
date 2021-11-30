/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:30:44 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:30:48 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_env_list *env_list)
{
    t_env *now;

    if (env_list->front == 0 || env_list->size == 0)
        return;
    now = env_list->front;
    int i = 0;
    while (now != 0)
    {
        write(1, " ", 1);
        write(1, now->key, ft_strlen(now->key));
        write(1, "|", 1);
        write(1, now->value, ft_strlen(now->value));
        write(1, "\n", 1);
        now = now->next;
        i++;
    }
}
