/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/12/20 19:06:13 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sc = 0;

void setting_signal()
{
    signal(SIGINT, main_sig_handler); // CTRL + C
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
        // printf("sc : %d\n", sc);
        str = readline("bash$ ");
        if (!str)
        {
            free(str);
            printf("\033[1A");
            printf("\033[6C");
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
    return (0);
}