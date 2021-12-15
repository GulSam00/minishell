/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:22:08 by sham              #+#    #+#             */
/*   Updated: 2021/12/15 17:36:16 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(void)
{
    char *path;

    path = getcwd(NULL, STDOUT_FILENO);
    write(STDOUT_FILENO, path, ft_strlen(path));
    write(STDOUT_FILENO, "\n", 1);   

    return (0);
}