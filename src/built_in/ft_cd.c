/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:34 by sham              #+#    #+#             */
/*   Updated: 2021/12/15 17:05:40 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(char *path)
{
    int result;
    printf ("char : %s\n", path);
    if (!path)
    {
        printf ("NULL!\n");
        result = chdir("/");

    }
    else
        result = chdir(path);
    // printf ("result : %d\n", result);
    // printf ("cur path : %s\n", getcwd(NULL, 0));
    if (result)
    {
        ft_error("cd: no such file or directory: ");
        ft_error(path);
        ft_error("\n");
    }
        
}