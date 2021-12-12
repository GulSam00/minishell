/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:38 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 12:12:40 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(int fd, int option, char *cmd)
{
    // 임시 변편
    int result;

    fd = 1;
    result += write(STDOUT_FILENO, cmd, ft_getlen(cmd));
    if (option)
        result += write(fd, "\n", 1);
    return result;
}