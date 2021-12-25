/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:51:56 by nasong            #+#    #+#             */
/*   Updated: 2021/12/25 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		len;
	int		index;
	char	*result;

	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	index = 0;
	while (*str1 != '\0')
	{
		result[index] = *str1;
		str1++;
		index++;
	}
	while (*str2 != '\0')
	{
		result[index] = *str2;
		str2++;
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*ft_strjoin_path(const char *str1, const char *str2)
{
	int		len;
	int		index;
	char	*result;

	len = ft_strlen(str1) + ft_strlen(str2) + 2;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	index = 0;
	while (*str1 != '\0')
	{
		result[index] = *str1;
		str1++;
		index++;
	}
	result[index] = '/';
	index++;
	while (*str2 != '\0')
	{
		result[index] = *str2;
		str2++;
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*ft_strjoin_with_char(const char *str1, const char *str2, const char c)
{
	int		len;
	int		index;
	char	*result;

	len = ft_strlen(str1) + ft_strlen(str2) + 2;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	index = 0;
	while (*str1 != '\0')
	{
		result[index] = *str1;
		str1++;
		index++;
	}
	result[index] = c;
	index++;
	while (*str2 != '\0')
	{
		result[index] = *str2;
		str2++;
		index++;
	}
	result[index] = '\0';
	return (result);
}
