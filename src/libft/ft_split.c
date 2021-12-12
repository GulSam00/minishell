/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:31:02 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 15:43:28 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_c_count(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (flag == 0)
			{
				flag = 1;
				count++;
			}
		}
		else
		{
			flag = 0;
		}
		i++;
	}
	return (count);
}

char	*ft_split_str(char const *s, char c, size_t start)
{
	size_t	i;
	char	*result;

	i = start;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	result = (char *)malloc(sizeof(char) * (i - start + 1));
	if (result == 0)
		return (0);
	ft_strlcpy(result, s + start, i - start + 1);
	return (result);
}

char	**ft_split_free(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	c_count;
	size_t	result_idx;
	size_t	now;

	if (s == 0)
		return (0);
	c_count = get_c_count(s, c);
	result = (char **)malloc(sizeof(char *) * (c_count + 1));
	if (result == 0)
		return (0);
	result_idx = 0;
	now = 0;
	while (result_idx < c_count)
	{
		while (s[now] != '\0' && s[now] == c)
			now++;
		result[result_idx] = ft_split_str(s, c, now);
		if (result[result_idx] == 0)
			return (ft_split_free(result, c_count));
		now += ft_strlen(result[result_idx++]);
	}
	result[result_idx] = 0;
	return (result);
}
