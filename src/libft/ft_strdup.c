/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:40:42 by nasong            #+#    #+#             */
/*   Updated: 2021/12/25 16:52:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		len;
	int		index;
	char	*result;

	index = 0;
	len = ft_strlen(str) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	while (index < len && str[index] != '\0')
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*ft_strndup(const char *str, int size)
{
	char	*result;
	int		index;

	index = 0;
	result = (char *)malloc(sizeof(char) * size);
	while (index < size && str[index] != '\0')
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
