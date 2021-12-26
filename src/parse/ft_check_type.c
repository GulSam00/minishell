/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:20:22 by nasong            #+#    #+#             */
/*   Updated: 2021/12/26 19:47:42 by marvin           ###   ########.fr       */
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
