/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:41:40 by sham              #+#    #+#             */
/*   Updated: 2022/01/03 19:37:10 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char *argv[], t_list *env_list, int out_dis)
{
	t_data	*now;
	t_env	*target;

	if (env_list == 0)
		return (0);
	if (argv[1] != 0)
	{
		ft_error("env", argv[1], "No such file or directory");
		return (127);
	}
	now = env_list->front;
	while (now != 0)
	{
		target = now->contents;
		if (target->value != 0)
		{
			write(out_dis, target->key, ft_strlen(target->key));
			write(out_dis, "=", 1);
			write(out_dis, target->value, ft_strlen(target->value));
			write(out_dis, "\n", 1);
		}
		now = now->next;
	}
	return (0);
}
