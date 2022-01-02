/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 12:59:09 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 12:59:46 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void	check_quotes_sub(char *str, int index, int *quotes, int *rm_quotes)
{
	if (str[index] == '\'')
	{
		if (*quotes == 0)
			*quotes = 1;
		else if (*quotes == 1)
			*quotes = 0;
		*rm_quotes = 1;
	}
	else if (str[index] == '\"')
	{
		if (*quotes == 0)
			*quotes = 2;
		else if (*quotes == 2)
			*quotes = 0;
		*rm_quotes = 1;
	}
}

void	check_env(char *result, t_list *env_list, int end)
{
	char	*temp;

	temp = change_to_env(result, env_list, end);
	free(result);
	result = temp;
}

char	*check_quotes(char *str, t_list *env_list, int quotes, int rm_quotes)
{
	char	*result;
	char	*temp;
	int		start;
	int		end;

	result = ft_strdup(str);
	start = 0;
	end = 0;
	while (result[end] != '\0')
	{
		check_quotes_sub(result, end, &quotes, &rm_quotes);
		if (result[end] == '$' && quotes != 1)
		{
			start = end;
			check_env(result, env_list, end);
		}
		end++;
	}
	if (rm_quotes == 1)
	{
		temp = ft_strndup(result + 1, ft_strlen(result) - 2);
		free(result);
		result = temp;
	}
	return (result);
}
