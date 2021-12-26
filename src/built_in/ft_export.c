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

#include "../minishell.h"

int print_env(t_list *env_list)
{
    t_data *now;
    t_env *target;

    if (env_list == 0)
        return (0);
    now = env_list->front;
    while (now != 0)
    {
        target = now->contents;
        write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
        write(STDOUT_FILENO, target->key, ft_strlen(target->key));
        if (target->value != 0)
        {
            write(STDOUT_FILENO, "=\"", 2);
            write(STDOUT_FILENO, target->value, ft_strlen(target->value));
            write(STDOUT_FILENO, "\"", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        now = now->next;
    }

    return (0);
}

int add_env(t_list *env_list, char *arg)
{
    t_env *new_env;
    char *key;
    char *value;
    int index;

    key = 0;
    value = 0;
    index = 0;
    new_env = malloc(sizeof(t_env));
    if (new_env == 0)
        return (1);
    while (arg[index] !='\0')
    {
        if (arg[index] == '=')
        {
            key = ft_strndup(arg, index);
            value = ft_strdup(arg + index + 1);
            if (get_value(env_list, key) != 0)
                pop_env_with_key(env_list, key);
            init_env(new_env, key, value);
            add_data(env_list, new_env);
            return (0);
        }
        index++;
    }
    init_env(new_env, ft_strdup(arg), 0);
    add_data(env_list, new_env);
    return (0);
}

int ft_export(t_list *env_list, char *argv[])
{
    int index;

    index = 1;
    if (argv[1] == 0)
    {
        print_env(env_list);
        return (0);
    }
    while (argv[index] != 0)
    {
        if (add_env(env_list, argv[index]) == 1)
            return (1);
        index++;
    }
    return (0);
}
