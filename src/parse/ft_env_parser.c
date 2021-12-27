/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:44 by nasong            #+#    #+#             */
/*   Updated: 2021/12/27 21:55:34 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(t_env *env, char *key, char *value)
{
	env->key = key;
	env->value = value;
}

int	ft_env_parser(t_list *env_list, char **envp)
{
	char	**split;
	int		index;
	t_env	*new_env;

	index = 0;
	while (envp[index] != 0)
	{
		new_env = malloc(sizeof(t_env));
		split = ft_split(envp[index], '=');
		init_env(new_env, ft_strdup(split[0]), ft_strdup(split[1]));
		free(split[0]);
		free(split[1]);
		free(split);
		add_data(env_list, new_env);
		index++;
	}
	return (0);
}
