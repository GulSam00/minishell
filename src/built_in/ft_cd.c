/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:34 by sham              #+#    #+#             */
/*   Updated: 2022/01/02 17:26:37 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *path, t_list *env_list)
{
	int		result;
	char	*home;

	home = get_value(env_list, "HOME");
	if (path)
		result = chdir(path);
	else
		result = chdir(home);
	if (result == -1)
	{
		ft_error("cd", path, strerror(2));
		return (1);
	}
	return (result);
}
