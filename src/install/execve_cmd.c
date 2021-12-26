/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/26 19:46:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void	execve_cmd_bult_in(char *cmd_name, \
t_cmd *cmd, t_list *env_list)
{
	int	state;

	handle_dis(cmd);
	if (!ft_cmpstr(cmd_name, "cd"))
		state = ft_cd(cmd->arg[1], env_list);
	else if (!ft_cmpstr(cmd_name, "pwd"))
		state = ft_pwd();
	else if (!ft_cmpstr(cmd_name, "echo"))
		state = ft_echo(cmd->arg);
	else if (!ft_cmpstr(cmd_name, "exit"))
		state = ft_exit(cmd->arg, is_forked);
	else if (!ft_cmpstr(cmd_name, "env"))
		state = ft_env(cmd->arg, env_list);
	else if (!ft_cmpstr(cmd_name, "export"))
		state = ft_export(env_list, cmd->arg);
	else if (!ft_cmpstr(cmd_name, "unset"))
		state = ft_unset(env_list, cmd->arg);
	exit(state);
}

void	execve_cmd_normal(char *cmd_name, t_cmd *cmd, t_list *env_list)
{
	pid_t	pid;
	char	**argv_env;
	int		status;

	handle_dis(cmd);
	argv_env = env_to_char(env_list);
	signal(SIGINT, execve_sig_handler);
	signal(SIGQUIT, execve_sig_handler);
	pid = fork();
	if (pid == 0)
		execve(cmd_name, cmd->arg, argv_env);
	else
		waitpid(pid, &status, 0);
	exit(WEXITSTATUS(status));
}
