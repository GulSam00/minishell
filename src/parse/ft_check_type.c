/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:51:14 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:51:17 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_discriptor(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (word[0] == '<')
	{
		if (len == 1)
			return (1);
		if (len == 2 && word[1] == '<')
			return (1);
	}
	else if (word[0] == '>')
	{
		if (len == 1)
			return (1);
		if (len == 2 && word[1] == '>')
			return (1);
	}
	return (0);
}

enum e_cmd_type	get_type(char *word)
{
	int	len;

	len = ft_strlen(word);
	if (len == 1 && word[0] == '|')
		return (PIPE);
	else if (is_discriptor(word) == 1)
		return (DISCRIPTOR);
	return (ARG);
}
