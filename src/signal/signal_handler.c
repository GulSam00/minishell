/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:50:39 by sham              #+#    #+#             */
/*   Updated: 2022/01/02 17:49:52 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("bash$ \n");
	}
	if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
	rl_replace_line("", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_redisplay();
}

void	execve_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		exit(130);
	}
	if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
		exit(131);
	}
}

void	heredoc_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf ("\n");
		exit(1);
	}
}
