/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:00:49 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 14:38:04 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free(char *str)
{
    if (str != NULL)
        free(str);
    str = NULL;
}

char *get_next_line(void)
{
    char *save;
    char *temp;
    char buf[2];
    int read_buf;

    write(1, "heredoc> ", 10);

    while (((read_buf = read(STDIN_FILENO, buf, 1)) > 0))
    {
        buf[read_buf] = '\0';
        if (save == NULL)
            temp = ft_strndup(buf, read_buf);
        else
            temp = ft_strjoin(save, buf);
        ft_free(save);
        save = temp;
    }
    if (read_buf == -1)
        return (NULL);
    return (save);
}