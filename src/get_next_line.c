/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:00:49 by sham              #+#    #+#             */
/*   Updated: 2021/11/24 20:05:20 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void ft_free(char *str)
{
    if (str != NULL)
        free(str);
    str = NULL;
}

int write_line(char **save, char **line, int index)
{
    char *temp;
    char *next_line;

    if (index >= 0)
    {
        *line = ft_strndup(*save, index);
        next_line = *save + index + 1;
        temp = ft_strndup(next_line, ft_strlen(next_line));
        ft_free(*save);
        *save = temp;
        return (1);
    }
    if (*save == NULL)
        *line = ft_strndup("", 0);
    else
    {
        *line = *save;
        *save = NULL;
    }
    return (0);
}

int find_nl(char *str)
{
    int i;

    i = 0;
    while (str != NULL && str[i] != '\0')
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
    return (FAIL);
}

int get_next_line(char *check, char **line)
{
    char *save;
    char *temp;
    char buf[BUFFER_SIZE + 1];
    int nl_index;
    int read_buf;

    if (line == NULL || BUFFER_SIZE <= 0)
        return (FAIL);
    while (((nl_index = find_nl(save)) == FAIL) &&
           ((read_buf = read(0, buf, BUFFER_SIZE)) > 0))
    {
        buf[read_buf] = '\0';
        if (save == NULL)
            temp = ft_strndup(buf, read_buf);
        else
            temp = ft_strjoin(save, buf);
        ft_free(save);
        save = temp;
    }
    if (read_buf == FAIL)
        return (FAIL);
    return (write_line(&save, line, nl_index));
}