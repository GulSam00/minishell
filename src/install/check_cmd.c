/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:43:02 by marvin            #+#    #+#             */
/*   Updated: 2021/12/25 17:43:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_built_in_array(char ***set_built_in_array)
{
	*set_built_in_array[0] = "cd";
	*set_built_in_array[1] = "echo";
	*set_built_in_array[2] = "env";
	*set_built_in_array[3] = "exit";
	*set_built_in_array[4] = "export";
	*set_built_in_array[5] = "pwd";
	*set_built_in_array[6] = "unset";
}

int	check_bulit_in(t_cmd *cmd)
{
	int		i;
	int		result;
	char	*built_in_list[7];

	set_built_in_array(&built_in_list);
	i = 0;
	while (i < 7)
	{
		result = ft_cmpstr(cmd->arg[0], built_in_list[i]);
		if (!result)
		{
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	check_cmd(t_cmd *cmd, t_list *env_list)
{
	struct stat		sb;
	int				result;
	char			*full_path;
	char			**path;

	path = ft_split(get_value(env_list, "PATH"), ':');
	if (!stat(cmd->arg[0], &sb))
	{
		execve_cmd_normal(cmd->arg[0], cmd, env_list);
		return (0);
	}
	while (*path)
	{
		full_path = ft_strjoin_path(*path, cmd->arg[0]);
		result = stat(full_path, &sb);
		if (!result)
		{
			execve_cmd_normal(full_path, cmd, env_list);
			return (0);
		}
		path++;
	}
	return (-1);
}

void	parse_cmd(t_cmd *cmd, t_list *env_list)
{
	int	result;

	result = check_bulit_in(cmd);
	if (!result)
		execve_cmd_bult_in(cmd->arg[0], cmd, env_list, 1);
	else
		result = check_cmd(cmd, env_list);
	if (result == -1)
	{
		ft_error(cmd->arg[0], NULL, "command not found");
		exit(127);
	}
	exit(0);
}
