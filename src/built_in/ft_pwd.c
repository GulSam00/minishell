/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:22:08 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:25:24 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(char *cmd)
{

    char *path;
    path = getcwd(NULL, 0);
    printf("before path : %s\n", path);
    printf("Result : %d\n", chdir(cmd));
    path = getcwd(NULL, 0);
    printf("after path : %s\n", path);

    if (!chdir(cmd))
        return (-1);
    return (0);
}