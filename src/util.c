/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:42:35 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 16:15:31 by sham             ###   ########.fr       */
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

int ft_error_message(int log)
{
    write(2, "error\n", 6);

    return (-1);
}

char **parse(int argc, char *argv[])
{
    char **command_list;
    int i;

    i = 1;
    command_list = (char **)malloc(sizeof(char *) * (argc - 1));
    while (i < argc)
    {
        printf("argv[%d] : %s\n", i, argv[i]);
        command_list[i] = ft_cpstr(argv[i]);
        printf("cp success! - %s\n", command_list[i]);
        i++;
    }
    return command_list;
}
