/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:55:13 by nasong            #+#    #+#             */
/*   Updated: 2022/01/09 15:36:34 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_list *env_list, int out_dis)
{
	t_data	*now;
	t_env	*target;

	if (env_list == 0)
		return (0);
	now = env_list->front;
	while (now != 0)
	{
		target = now->contents;
		write(out_dis, "declare -x ", ft_strlen("declare -x "));
		write(out_dis, target->key, ft_strlen(target->key));
		if (target->value != 0)
		{
			write(out_dis, "=\"", 2);
			write(out_dis, target->value, ft_strlen(target->value));
			write(out_dis, "\"", 1);
		}
		write(out_dis, "\n", 1);
		now = now->next;
	}
	return (0);
}

int	add_env(t_list *env_list, char *arg)
{
	t_env	*new_env;
	char	*key;
	char	*value;
	int		index;

	index = 0;
	new_env = malloc(sizeof(t_env));
	while (arg[index] != '\0')
	{
		if (arg[index] == '=')
		{
			key = ft_strndup(arg, index);
			value = ft_strdup(arg + index + 1);
			pop_env_with_key(env_list, key);
			init_env(new_env, key, value);
			add_data(env_list, new_env);
			return (0);
		}
		index++;
	}
	pop_env_with_key(env_list, arg);
	init_env(new_env, ft_strdup(arg), 0);
	add_data(env_list, new_env);
	return (0);
}

int	ft_export(t_list *env_list, char *argv[], int out_dis)
{
	int	index;
	int	result;

	index = 1;
	result = 0;
	if (argv[1] == 0)
	{
		print_env(env_list, out_dis);
		return (0);
	}
	while (argv[index] != 0)
	{
		if (ft_isdigit(argv[index][0]) != 0 || argv[index][0] == '=')
		{
			ft_error_sing_dot("export", argv[index], "not a valid identifier");
			result = 1;
		}
		else
		{
			if (add_env(env_list, argv[index]) == 1)
				return (1);
		}
		index++;
	}
	return (result);
}
