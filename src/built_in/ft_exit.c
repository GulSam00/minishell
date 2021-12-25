/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:11:37 by sham              #+#    #+#             */
/*   Updated: 2021/12/25 20:55:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

static int	ft_is_num(char *str, int sign, int is_num)
{
	unsigned long long	num;

	sign = 1;
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

static long long	ft_atoll(char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || \
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

int	ft_exit(char *argv[], int is_forked)
{
	if (argv[1] == NULL)
	{
		if (!is_forked)
			write(1, "exit \n", 7);
		exit(0);
	}
	else if (ft_is_num(argv[1], 1, 0))
	{
		ft_error("exit", argv[1], "numeric argument required");
		exit(255);
	}
	else if (!ft_is_num(argv[1], 1, 0) && argv[2] == NULL)
	{
		write(1, "exit \n", 7);
		exit(ft_atoll(argv[1]));
	}
	else
	{
		ft_error("exit", NULL, "too many arguments");
		return (1);
	}
}
