/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:44 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 17:00:32 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env_parser(t_list *env_list, char **envp)
{
	char **split;
	int index;
	t_env *new_env;

	index = 0;
	while (envp[index] != 0)
	{
		new_env = malloc(sizeof(t_env));
		split = ft_split(envp[index], '=');
		init_env(new_env, split[0], split[1]);
		add_data(env_list, new_env);
		index++;
	}
	return (0);
}
