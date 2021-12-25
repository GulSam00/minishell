/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:11:37 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 14:15:40 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int sc;

static int ft_is_num(char *str)
{
    int sign;
    unsigned long long num;
    int is_num;
    
    sign = 1;
    num = 0;
    is_num = 0;
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
        if (num > LLONG_MAX && sign == 1)
            return (-1);
        if (num > (unsigned long long)LLONG_MIN && sign == -1)
            return (-1);
        is_num = 1;
    }
    if ((*(str - 1) != '-' || *(str - 1) != '+') && is_num)
        return (0);
    else
        return (-1);
}
static long long ft_atoll(char *str)
{
    int sign;
    long long num;

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
    }
    return ((long long)(num * sign));
}

int ft_exit(char *argv[], int is_forked)
{
    if (argv[1] == NULL)
    {
		if (!is_forked)
        	write(1, "exit \n", 7);
        exit(0);
    }
    else if (ft_is_num(argv[1]))
    {
        ft_error("exit", argv[1], "numeric argument required"); //  exit의 에러는 특별한 에러라 별도 처리.
        exit(255);
        // exit의 인자가 숫자가 아닐 경우 255 상태코드로 exit
    }
    else if (!ft_is_num(argv[1]) && argv[2] == NULL) //  숫자인지 아닌지 식별, 숫자 뒤에 문자열 있어도 걸러내야 함
    {
        write(1, "exit \n", 7);
        exit(ft_atoll(argv[1]));
        // 상태 코드가 exit의 인자로 들어감.
    }
    else
    {
        ft_error("exit", NULL, "too many arguments");
        // 상태코드 1
        return (1);
    }
}
