/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:11:37 by sham              #+#    #+#             */
/*   Updated: 2021/12/17 14:54:45 by sham             ###   ########.fr       */
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
        if (ft_atoi(argv[1])) //  숫자인지 아닌지 식별, 숫자 뒤에 문자열 있어도 걸러내야 함
        {
            exit(ft_atoi(argv[1]));
            // 상태 코드가 exit의 인자로 들어감.
        }
        else
        {
            ft_error("exit", argv[1], "numeric argument required"); // https://velog.io/@hidaehyunlee/minishell-4.-%EC%A2%85%EB%A3%8C%EC%83%81%ED%83%9C%EC%99%80-%EC%97%90%EB%9F%AC%EB%A9%94%EC%84%B8%EC%A7%80-%EC%B2%98%EB%A6%AC 참조. exit의 에러는 특별한 에러라 별도 처리.
            exit(255);                                              // exit의 인자가 숫자가 아닐 경우 255 상태코드로 exit
        }
    }
    else
    {
        ft_error("exit", NULL, "too many arguments");
    }
}