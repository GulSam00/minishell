/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:47:23 by sham              #+#    #+#             */
/*   Updated: 2021/11/24 20:01:21 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#ifndef OPEN_MAX
#define OPEN_MAX 10240
#endif

#define FAIL -1

int get_next_line(int fd, char **line);
size_t ft_strlen(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(const char *str, ssize_t offst);

#endif