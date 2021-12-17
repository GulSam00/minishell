/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/12/17 11:36:57 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        // printf("\033[K"); //지워버리는 것을 원하지는 않았음.
        printf("bash$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);

    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다. 왜 안돼!!!

    rl_redisplay(); // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
}

int init_main(t_list *cmd_list, t_list *env_list, char **envp)
{
    int result;
    struct termios term;

    result = 0;
    init_list(cmd_list);
    init_list(env_list);
    result += ft_env_parser(env_list, envp);
    result += tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    result += tcsetattr(STDIN_FILENO, TCSANOW, &term);
    setting_signal();
    return (result);
}

int main(int argc, char **argv, char **envp)
{
    char *str;
    t_list cmd_list;
    t_list env_list;

    if (init_main(&cmd_list, &env_list, envp))
        return (-1);
    if (argc && argv)
        ;
    while (1)
    {
        str = readline("bash$ ");
        if (!str)
        {
            free(str);
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
            add_history(str);
            ft_parser(&cmd_list, str);
            fork_cmd(&cmd_list, &env_list);
            free(str);
        }
    }
    printf("main end!\n");
    return (0);
}