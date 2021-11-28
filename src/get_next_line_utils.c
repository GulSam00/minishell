/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:42:59 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 16:12:46 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strlen(const char *s)
{
    size_t n;

    n = 0;
    while (s[n])
        n++;
    return (n);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t total_len;
    size_t s1_i;
    size_t s2_i;
    char *str;

    s1_i = 0;
    s2_i = 0;
    if (!s1 || !s2)
        return (0);
    total_len = ft_strlen(s1) + ft_strlen(s2);
    if ((str = (char *)malloc(total_len + 1)) == 0)
        return (0);
    while (s1[s1_i] != '\0')
    {
        str[s1_i] = s1[s1_i];
        s1_i++;
    }
    while (s2[s2_i] != '\0')
    {
        str[s1_i + s2_i] = s2[s2_i];
        s2_i++;
    }
    str[s1_i + s2_i] = '\0';
    return (str);
}

char *ft_strndup(const char *str, ssize_t offst)
{
    char *result;
    int i;

    i = 0;
    if (!(result = (char *)malloc(sizeof(char) * (offst + 1))))
        return (0);
    while (str[i] != '\0' && i < offst)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}