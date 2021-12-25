/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:34 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 20:40:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *path, t_list *env_list)
{
	int result;
	char *home;

	home = get_value(env_list, "HOME");
	if (path)
		result = chdir(path);
	else if (!path && home)
	{
		result = chdir(home);
	}
	else
		result = 0;
	if (result == -1)
	{
		ft_error("cd", path, strerror(2));
		return (1);
	}
	return (result);
	// exit(g_sc); 파이프와 연결됬을 때는 exit 해야 함.
}
