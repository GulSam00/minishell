/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:50:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/20 19:23:24 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void main_sig_handler(int signal)
{

    // printf("%d\n", signal_flag);
    if (signal == SIGINT)
    {
        printf("bash$ \n"); // 기존의 readline()으로 입력한 라인 (프롬프트에 입력한 문자열 포함)에 덮어씌여진다.
    }
    if (signal == SIGQUIT)
    {
        printf("Quit: 3\n");
    }

    rl_replace_line("", 1);     // 프롬프트의 문자열을 인자와 같이 바꿔준다. ""로 채워주지 않으면 이전에 터미널에 친 내용이 그대로 올라간다...
    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다? rl_redisplay를 사용하기 전에는 무조건 사용해야 한다.
        exit(1);
    rl_redisplay(); // readline()안의 문자열을 보여준다. 없다면 키보드를 입력하지 전까지 readline()의 내용이 보이지 않는다.
}

void execve_sig_handler(int signal)
{

    // printf("%d\n", signal_flag);
    if (signal == SIGINT)
    {
        printf("\n");
    }
    if (signal == SIGQUIT)
    {
        printf("Quit: 3\n");
    }
}


void heredoc_sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf ("\n");
        exit(1);

    }
}