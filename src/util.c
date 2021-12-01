/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:42:35 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 12:00:10 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_getlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_cpstr(char *str)
{
    char *temp;
    int i;

    i = 0;
    temp = (char *)malloc(ft_getlen(str) + 1);
    while (str[i])
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    return temp;
}

int ft_cmpstr(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i])
    {
        if (str1[i] != str2[i])
            return -1;
        i++;
    }
    if (str2[i])
        return -1;
    return 0;
}

int ft_error_message(char *message)
{
    write(2, message, ft_getlen(message));
    write(2, "\n", 1);

    return (-1);
}
