/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:40:51 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 15:41:10 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t n)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (source == 0)
		return (0);
	while (source[src_len] != '\0')
		src_len++;
	while (i + 1 < n && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	if (n != 0)
		destination[i] = '\0';
	return (src_len);
}
