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
/*
void test_env()
{
    t_env_list env_list;

    env_list.size = 0;
    env_list.front = 0;
    ft_export(&env_list, "test_key1", "test_value1");
    ft_export(&env_list, "test_key2", "test_value2");
    ft_env(&env_list);
    ft_unset(&env_list, "test_key1");
    ft_env(&env_list);
    free_all_envs(&env_list);
    ft_env(&env_list);
}

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
*/
int ft_env(t_list *env_list)
{
    t_data *now;
    t_env *target;

    if (env_list == 0)
        return (0);
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
