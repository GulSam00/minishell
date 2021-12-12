/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:20:22 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 15:12:00 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_cmd(char *word)
{
	int len;

	len = ft_strlen(word);

	return (0);
}

enum e_cmd_type get_type(char *word)
{
	int len;

	len = ft_strlen(word);
	if (len == 1 && word[0] == '|')
		return (PIPE);
	else if (is_cmd(word) == 1)
		return (CMD);
	return (ARG);
}
