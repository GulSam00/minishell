/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:38 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 20:49:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char *argv[])
{
	int	option;
	int	i;

	i = 1;
	option = 0;
	if (argv[i] && !ft_cmpstr(argv[i], "-n"))
	{
		option = 1;
		i++;
	}
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!option)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
