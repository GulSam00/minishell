/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/12/12 14:06:37 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        //printf("\033[K"); 지워버리는 것을 원하지는 않았음.
        printf("nanoshell$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}
int main(void)
{
    char *str;
    t_list list;
    init_list(&list);
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    setting_signal();
    // 환경변수
    while (1)
    {
        str = readline("nanoshell$ ");
        ft_parser(&list, str);
        if (!str)
        {
            printf("\033[1A");
            printf("\033[10C");
            printf(" exit\n");
            exit(-1);
        }
        else if (*str == '\0')
        {
            free(str);
        }
        else
        {
            // fork_cmd(cmd, env);
            add_history(str);
            printf("%s\n", str);
            free(str);
        }
    }
    return (0);
}