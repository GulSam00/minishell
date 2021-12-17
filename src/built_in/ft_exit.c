/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:11:37 by sham              #+#    #+#             */
/*   Updated: 2021/12/17 11:47:36 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_atoi(const char *str)
{
    long sign;
    long num;

    sign = 1;
    num = 0;
    while (*str == '\t' || *str == '\n' || *str == '\v' ||
           *str == '\f' || *str == '\r' || *str == 32)
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    while (*str && *str >= '0' && *str <= '9')
    {
        num = 10 * num + (*str - '0');
        str++;
        if (num > 2147483647 && sign == 1)
            return (-1);
        if (num < -2147483648 && sign == -1)
            return (0);
    }
    return ((int)(num * sign));
}

void ft_exit(char *argv[])
{
    if (argv[1] == NULL)
    {
        write(1, "exit \n", 7);
        exit(0);
    }
    else if (argv[2] == NULL)
    {
        write(1, "exit \n", 7);
        if (ft_atoi(argv[1])) // 0은 식별해야 함...
        {
            exit(ft_atoi(argv[1]));
            // 상태 코드가 exit의 인자로 들어감.
        }
        else
        {
            ft_error("bash: exit: ");
            ft_error(argv[1]);
            ft_error(": numeric argument required\n");
            exit(255); // exit의 인자가 숫자가 아닐 경우 255 상태코드로 exit
        }
    }
    else
    {
        ft_error("bash: exit: too many arguments\n");
    }
}