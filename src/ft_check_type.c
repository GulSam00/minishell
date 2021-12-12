/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:20:22 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 11:46:35 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	is_cmd(char *word)
{
	int len;

	len = ft_strlen(word);
	if (ft_strlen("echo") == len && ft_strncmp("echo", word, len) == 0)
	{
		return (1);
	}
	return (0);
}

enum e_cmd_type get_type(char *word)
{
	int len;

	len = ft_strlen(word);
	if (len == 1 && word[0] == '|')
		return (PIPE);
	else if(is_cmd(word) == 1)
		return (CMD);
	return (ARG);
}
