/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:47:18 by marvin            #+#    #+#             */
/*   Updated: 2021/12/26 19:47:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

char	*get_word(char *str)
{
	int	idx;
	int	first_quotes;

	idx = 0;
	first_quotes = 0;
	if (str[idx] == '\'')
	{
		first_quotes = 1;
		idx++;
	}
	else if (str[idx] == '\"')
	{
		first_quotes = 2;
		idx++;
	}
	while (str[idx] != '\0')
	{
		if (str[idx] == '\'')
		{
			if (first_quotes == 0)
				break ;
			else if (first_quotes == 1)
			{
				idx++;
				break ;
			}
		}
		else if (str[idx] == '\"')
		{
			if (first_quotes == 0)
				break ;
			else if (first_quotes == 2)
			{
				idx++;
				break ;
			}
		}
		if (str[idx] == ' ' && first_quotes == 0)
			break ;
		idx++;
	}
	return (ft_strndup(str, idx));
}

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

char	*change_to_env(char *str, t_list *env_list, int start)
{
	int		index;
	char	*target;
	char	*env;
	char	*temp;

	index = start + 1;
	while (str[index] != ' ' && str[index] != '\'' \
	&& str[index] != '\"' && str[index] != '\0')
		index++;
	target = ft_strndup(str + start + 1, index - start - 1);
	env = ft_strdup(get_value(env_list, target));
	if (env == 0)
	{
		if (ft_strlen(target) == 1 && target[0] == '?')
			env = ft_itoa(g_sc);
		else
			env = ft_strdup("");
	}
	temp = change_word(str, env, start, index);
	free(target);
	free(env);
	return (temp);
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
		if (result[end] == '\'')
		{
			if (quotes == 0)
				quotes = 1;
			else if (quotes == 1)
				quotes = 0;
			rm_quotes = 1;
		}
		else if (result[end] == '\"')
		{
			if (quotes == 0)
				quotes = 2;
			else if (quotes == 2)
				quotes = 0;
			rm_quotes = 1;
		}
		if (result[end] == '$' && quotes != 1)
		{
			start = end;
			temp = change_to_env(result, env_list, end);
			free(result);
			result = temp;
		}
		end++;
	}
	if (rm_quotes == 1)
	{
		temp = ft_strndup(result + 1, ft_strlen(result) - 2);
		free(result);
		result = temp;
		rm_quotes = 0;
	}
	return (result);
}

int		ft_div_input(t_list *word_list, char *input, t_list *env_list)
{
	int		now;
	char	*word;
	char	*result;

	now = 0;
	word = 0;
	while (input[now] != '\0')
	{
		if (input[now] == ' ')
		{
			now++;
			continue ;
		}
		word = get_word(input + now);
		if (word == 0)
			return (-1);
		now += ft_strlen(word);
		result = check_quotes(word, env_list, 0, 0);
		free(word);
		word = result;
		result = 0;
		add_data(word_list, word);
	}
	return (0);
}
