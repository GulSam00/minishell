/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:34 by sham              #+#    #+#             */
/*   Updated: 2021/12/17 14:49:41 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(char *path, t_list *env_list)
{
    int result;
    char *home;

    home = get_value(env_list, "HOME");
    if (path)
        result = chdir(path);
    else if (!path && home)
    {
        result = chdir(home);
    }
    else
        result = 0;
    if (result == -1)
    {
        ft_error("cd", path, strerror(2));
     }
}