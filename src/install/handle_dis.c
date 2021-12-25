/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:26:04 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 18:21:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_sc;

int	ft_d_right_paste(char *dst)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp == -1)
		return (-1);
	if (dup2(temp, STDOUT_FILENO) == -1)
		return (-1);
	return (close(temp));
}

int	ft_d_right_append(char *dst)
{
	int	temp;

	temp = open(dst, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp == -1)
		return (-1);
	if (dup2(temp, STDOUT_FILENO) == -1)
		return (-1);
	return (close(temp));
}

int	ft_d_left_normal(char *dst)
{
	int	temp;

	temp = open(dst, O_RDONLY);
	if (dup2(temp, STDIN_FILENO) == -1)
		return (-1);
	return (close(temp));
}

int	ft_d_left_heredoc(char *dst)
{
	char	*str;
	int		fd[2];
	int		status;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
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
			write(fd[1],"\n", 1);
			free(str);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0); 
		g_sc = WEXITSTATUS(status);
		if (g_sc == 1)
			exit(1);
		if (g_sc == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
	}
	return (0);
}

int	handle_dis(t_cmd *cmd)
{
	t_list			*dis_list;
	t_data			*cur_dis;
	t_discriptor	*dis;

	dis_list = &cmd->discriptor;
	cur_dis = dis_list->front;
	while (cur_dis)
	{
		dis = cur_dis->contents;
		if (dis->type == IN)
			ft_d_left_normal(dis->file_name);
		else if (dis->type == DOUBLE_IN)
			ft_d_left_heredoc(dis->file_name);
		else if (dis->type == OUT)
			ft_d_right_paste(dis->file_name);
		else if (dis->type == DOUBLE_OUT)
			ft_d_right_append(dis->file_name);
		else
			return (-1);
		cur_dis = cur_dis->next;
	}
	return (0);
}
