/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:29:56 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:31:16 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unset(t_list *env_list, char *argv[])
{
    int index;

    index = 1;
    while (argv[index] != 0)
    {
        pop_env_with_key(env_list, argv[index]);
        index++;
    }
    return (0);
}
