/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 20:35:11 by marvin            #+#    #+#             */
/*   Updated: 2021/12/25 20:35:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_count(long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

size_t	ft_itoa_pow(int n, size_t count)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 1;
	while (i < count)
	{
		result *= n;
		i++;
	}
	return (result);
}

void	ft_itoa_set(long num, char *result, size_t len)
{
	size_t	i;
	size_t	div;

	i = 0;
	div = ft_itoa_pow(10, len);
	if (num < 0)
	{
		result[i++] = '-';
		num *= -1;
		div /= 10;
	}
	while (i <= len)
	{
		result[i++] = '0' + (num / div);
		num %= div;
		div /= 10;
	}
	result[i] = '\0';
}

char	*ft_itoa(long n)
{
	char	*result;
	long	num;
	size_t	len;
	size_t	i;

	i = 0;
	num = n;
	len = get_count(n);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	ft_itoa_set(num, result, len);
	return (result);
}
