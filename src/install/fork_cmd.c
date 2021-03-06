/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:56:29 by sham              #+#    #+#             */
/*   Updated: 2022/01/03 14:35:22 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

static void	pid_child(int prev_input, int *fd, t_data *data)
{
	if (prev_input == -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (data->next == NULL)
	{
		close(fd[1]);
		dup2(prev_input, STDIN_FILENO);
		close(prev_input);
	}
	else
	{
		dup2(prev_input, STDIN_FILENO);
		close(prev_input);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	single_cmd(t_data *data, t_list *env_list, int status)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = data->contents;
	if (!check_bulit_in(cmd, 2))
		execve_cmd_sing_env(cmd->arg[0], cmd, env_list);
	else
	{	
		if (handle_dis(cmd) == -1)
		{
			g_sc = 1;
			close_main_fd(cmd);
			return ;
		}
		pid = fork();
		if (pid == 0)
			parse_cmd(cmd, env_list, 0);
		else
		{
			close_main_fd(cmd);
			waitpid(pid, &status, 0);
			g_sc = WEXITSTATUS(status);
		}
	}
}

static void	multi_cmd(t_data *data, t_list *env_list, int status)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		fd[2];
	int		prev_input;

	prev_input = -1;
	while (data)
	{
		cmd = data->contents;
		pipe(fd);
		multi_cmd_while(cmd);
		pid = fork();
		if (pid == 0)
		{
			pid_child(prev_input, fd, data);
			parse_cmd(cmd, env_list, 1);
		}
		data = data->next;
		close(fd[1]);
		if (prev_input != -1)
			close(prev_input);
		prev_input = fd[0];
	}
	multi_cmd_wait_child(prev_input, pid, cmd, status);
}

void	fork_cmd(t_list *cmd_list, t_list *env_list)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	status = 0;
	if (cmd_list->size == 1)
		single_cmd(cmd_list->front, env_list, status);
	else
		multi_cmd(cmd_list->front, env_list, status);
	signal(SIGINT, main_sig_handler);
}
