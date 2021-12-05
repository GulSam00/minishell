/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:51:56 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 21:52:26 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	int len;
	int index;
	char *result;

	len = ft_strlen(str1) + ft_strlen(str2);
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
