/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2022/01/08 16:45:41 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void	execve_cmd_sing_env(char *cmd_name, \
t_cmd *cmd, t_list *env_list)
{
	int	state;
	int	out_dis;

	state = 0;
	if (handle_dis(cmd) == -1)
	{
		g_sc = 1;
		return ;
	}
	out_dis = return_out_dis(cmd);
	if (!ft_cmpstr(cmd_name, "env"))
		state = ft_env(cmd->arg, env_list, out_dis);
	else if (!ft_cmpstr(cmd_name, "export"))
		state = ft_export(env_list, cmd->arg, out_dis);
	else if (!ft_cmpstr(cmd_name, "unset"))
		state = ft_unset(env_list, cmd->arg);
	else if (!ft_cmpstr(cmd_name, "exit"))
		state = ft_exit(cmd->arg, 0);
	else
		state = ft_cd(cmd->arg[1], env_list);
	close_main_fd(cmd);
	g_sc = state;
}

void	execve_cmd_bult_in(char *cmd_name, \
t_cmd *cmd, t_list *env_list, int is_forked)
{
	int	state;

	state = 0;
	dup_cmd_dis(cmd);
	if (!ft_cmpstr(cmd_name, "cd"))
		state = ft_cd(cmd->arg[1], env_list);
	else if (!ft_cmpstr(cmd_name, "pwd"))
		state = ft_pwd();
	else if (!ft_cmpstr(cmd_name, "echo"))
		state = ft_echo(cmd->arg);
	else if (!ft_cmpstr(cmd_name, "exit"))
		state = ft_exit(cmd->arg, is_forked);
	else if (!ft_cmpstr(cmd_name, "env"))
		state = ft_env(cmd->arg, env_list, STDOUT_FILENO);
	else if (!ft_cmpstr(cmd_name, "export"))
		state = ft_export(env_list, cmd->arg, STDOUT_FILENO);
	else
		state = ft_unset(env_list, cmd->arg);
	exit(state);
}

void	execve_cmd_normal(char *cmd_name, t_cmd *cmd, t_list *env_list)
{
	pid_t	pid;
	char	**argv_env;
	int		status;

	argv_env = env_to_char(env_list);
	signal(SIGINT, execve_sig_handler);
	signal(SIGQUIT, execve_sig_handler);
	pid = fork();
	if (pid == 0)
	{
		dup_cmd_dis(cmd);
		execve(cmd_name, cmd->arg, argv_env);
	}
	else
		waitpid(pid, &status, 0);
	exit(WEXITSTATUS(status));
}
