/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/12/19 19:50:32 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sc;

void sig_handler(int signal)
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
        // printf("bash$ new ");
        str = readline("bash$ ");
        if (!str)
        {
            free(str);
            printf("\033[1A");
            printf("\033[10C");
            printf(" exit\n");
            exit(0);
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