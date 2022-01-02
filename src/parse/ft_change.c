/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:11:41 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:50:58 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

char	*change_word(char *str, char *sub_str, int start, int end)
{
	char	*front;
	char	*temp;
	char	*back;

	front = ft_strndup(str, start);
	back = ft_strdup(str + end);
	temp = ft_strjoin(front, sub_str);
	free(front);
	front = temp;
	temp = ft_strjoin(front, back);
	free(front);
	free(back);
	front = temp;
	return (front);
}

char	*change_str_with_env(char *str, int start, int end, t_list *env_list)
{
	char	*target;
	char	*env;
	char	*result;

	target = ft_strndup(str + start + 1, end - start - 1);
	env = ft_strdup(get_value(env_list, target));
	if (env == 0)
	{
		if (ft_strlen(target) == 1 && target[0] == '?')
			env = ft_itoa(g_sc);
		else if (ft_strlen(target) == 1 && target[0] == '$')
			env = ft_itoa(getpid());
		else
			env = ft_strdup("");
	}
	result = change_word(str, env, start, end);
	free(target);
	free(env);
	return (result);
}

char	*change_to_env(char *str, t_list *env_list, int start)
{
	int		index;
	char	*result;

	index = start + 1;
	while (str[index] != ' ' && str[index] != '\'' \
	&& str[index] != '\"' && str[index] != '\0')
	{
		if (str[index - 1] == '$')
		{
			if (str[index] == '?' || str[index] == '$')
			{
				index++;
				break ;
			}
		}
		index++;
	}
	result = change_str_with_env(str, start, index, env_list);
	return (result);
}
