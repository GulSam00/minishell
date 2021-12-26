/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:41:40 by sham              #+#    #+#             */
/*   Updated: 2021/12/06 10:41:51 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(char *argv[], t_list *env_list)
{
    t_data *now;
    t_env *target;

    if (env_list == 0)
        return (0);
    if (argv[1] != 0)
    {
        //env: a: No such file or directory
        return (127);
    }
    now = env_list->front;
    while (now != 0)
    {
        target = now->contents;
        if (target->value != 0)
        {
            write(STDOUT_FILENO, target->key, ft_strlen(target->key));
            write(STDOUT_FILENO, "=", 1);
            write(STDOUT_FILENO, target->value, ft_strlen(target->value));
            write(STDOUT_FILENO, "\n", 1);
        }
        now = now->next;
    }

    return (0);
}
