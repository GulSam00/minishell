/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 20:39:13 by marvin            #+#    #+#             */
/*   Updated: 2022/01/02 18:18:46 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

static void	heredoc_child(int *fd, char *dst)
{
	char	*str;

	signal(SIGINT, heredoc_sig_handler);
	close(fd[0]);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			free(str);
			break ;
		}
		else if (!ft_cmpstr(str, dst))
		{
			free(str);
			break ;
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
	}
	close(fd[1]);
	exit(0);
}

int	ft_d_left_heredoc(char *dst, t_discriptor *dis)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		heredoc_child(fd, dst);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		g_sc = WEXITSTATUS(status);
		if (g_sc == 1)
			return (-2);
		dis->value = fd[0];
	}
	return (0);
}
