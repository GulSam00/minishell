/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:40:42 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 21:46:20 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

char	*ft_strdup(const char *str)
{
	int	len;
	int	index;
	char	result;

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
	int	index;

	index = 0;
	result = (char *)malloc(sizeof(char) *size);
	while (index < size && str[index] != '\0')
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
