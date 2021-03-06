/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:47:55 by sham              #+#    #+#             */
/*   Updated: 2022/01/03 13:31:12 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_sing_dot(char *cmd, char *arg, char *message)
{
	write(2, "bash: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		write(2, "'", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "'", 1);
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	ft_error(char *cmd, char *arg, char *message)
{
	write(2, "bash: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
