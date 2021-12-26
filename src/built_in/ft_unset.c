/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:29:56 by sham              #+#    #+#             */
/*   Updated: 2021/12/26 18:10:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_list *env_list, char *argv[])
{
	int	index;
    int result;

	index = 1;
    result = 0;
	while (argv[index] != 0)
	{
		if (ft_isdigit(argv[index][0]) != 0 || argv[index][0] == '=')
		{
			ft_error_sing_dot("unset", argv[index], "not a valid identifier");
			result = 1;
		}
		else
			pop_env_with_key(env_list, argv[index]);
		index++;
	}
	return (result);
}
