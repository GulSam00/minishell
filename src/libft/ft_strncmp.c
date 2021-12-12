/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:03:02 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 22:20:09 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_strncmp(const char *str1, const char *str2, int len)
{
    int i;

    i = 0;
    while ((str1[i] != '\0' || str2[i] != '\0') && i < len)
    {
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
        i++;
    }
    return (0);
}
