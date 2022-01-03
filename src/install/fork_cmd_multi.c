/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:32:06 by sham              #+#    #+#             */
/*   Updated: 2022/01/03 14:33:56 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void	multi_cmd_wait_child(int prev_input, pid_t pid, t_cmd *cmd, int status)
{
	close(prev_input);
	close_main_fd(cmd);
	waitpid(pid, &status, 0);
	g_sc = WEXITSTATUS(status);
}

void	multi_cmd_while(t_cmd *cmd)
{
	if (handle_dis(cmd) == -1)
	{
		g_sc = 1;
		close_main_fd(cmd);
		return ;
	}
}
