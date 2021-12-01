/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/01 15:54:29 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execve_function(char **arg, char **env)
{
    pid_t pid;
// $PATH
 // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
 // : 를 기준으로 나눠서 검증해야 한다.
    pid = fork();
    if (pid > 0)
        return 0;
    else if (pid == 0)
    { // 자식 코드
       
        execve("/bin/cat", arg, env);
        exit(0);
    }
    else
    { // fork 실패
        printf("fork Fail! \n");
        return -1;
    }
    return ;
}