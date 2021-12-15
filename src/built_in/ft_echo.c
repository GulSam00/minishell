/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:19:38 by sham              #+#    #+#             */
/*   Updated: 2021/12/15 17:10:27 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(int option, char *cmd)
{
    // 임시 변편
    int result;

    result += write(STDOUT_FILENO, cmd, ft_strlen(cmd));
    if (option)
        result += write(STDOUT_FILENO, "\n", 1);
    
}