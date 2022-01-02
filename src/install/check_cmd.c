/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:43:02 by marvin            #+#    #+#             */
/*   Updated: 2021/12/28 20:45:53 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**set_built_in_array(void)
{
	char	**array;

	array = malloc(sizeof(char *) * 7);
	array[0] = "pwd";
	array[1] = "echo";
	array[2] = "cd";
	array[3] = "exit";
	array[4] = "env";
	array[5] = "unset";
	array[6] = "export";
	return (array);
}

int	check_bulit_in(t_cmd *cmd, int range)
{
	int		result;
	char	**built_in_list;

	built_in_list = set_built_in_array();
	while (range < 7)
	{
		result = ft_cmpstr(cmd->arg[0], built_in_list[range]);
		if (!result)
		{
			free(built_in_list);
			return (0);
		}
		range++;
	}
	free(built_in_list);
	return (-1);
}

static int	check_cmd(t_cmd *cmd, t_list *env_list)
{
	struct stat		sb;
	int				result;
	char			*full_path;
	char			**path;

	path = ft_split(get_value(env_list, "PATH"), ':');
	if (path == NULL)
		return (1);
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

void	parse_cmd(t_cmd *cmd, t_list *env_list, int is_forked)
{
	int	result;

	result = check_bulit_in(cmd, 0);
	if (!result)
		execve_cmd_bult_in(cmd->arg[0], cmd, env_list, is_forked);
	else
		result = check_cmd(cmd, env_list);
	if (result)
	{
		if (result == -1)
			ft_error(cmd->arg[0], NULL, "command not found");
		else
			ft_error(cmd->arg[0], NULL, "No such file or directory");
		exit(127);
	}
	exit(0);
}
