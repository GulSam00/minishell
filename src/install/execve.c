/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:04:51 by sham              #+#    #+#             */
/*   Updated: 2021/12/20 12:03:52 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int sc;

void execve_cmd_bult_in(char *cmd_name, t_cmd *cmd, t_list *env_list)
{
    handle_dis(cmd);
    if (!ft_cmpstr(cmd_name, "cd"))
        ft_cd(cmd->arg[1], env_list);
    else if (!ft_cmpstr(cmd_name, "pwd"))
        ft_pwd();
    else if (!ft_cmpstr(cmd_name, "echo"))
        ft_echo(cmd->arg);
    else if (!ft_cmpstr(cmd_name, "exit"))
        ft_exit(cmd->arg);

    // 공통 : 파일 디스크립터 조정
    // 실행하고 exit으로 종료?
}

static void ano_sig_handler(int signal)
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

void execve_cmd_normal(char *cmd_name, t_cmd *cmd, t_list *env_list)
{
    char **argv_env;
    pid_t pid;
    int status;

    handle_dis(cmd);

    argv_env = env_to_char(env_list);
    // 포크 떠서 실행하고 부모 프로세스는 exit으로 종료?
    if (!ft_cmpstr(cmd->arg[0], "cat"))
    {
        signal(SIGINT, ano_sig_handler);
        signal(SIGQUIT, ano_sig_handler);
    }
    pid = fork();

    if (pid == 0)
        execve(cmd_name, cmd->arg, argv_env);
    else
        waitpid(pid, &status, 0); // 삭제 시 cat 정상 입력 안됨, Ctrl + \ 도...
    exit(WEXITSTATUS(status));
}

int check_bulit_in(t_cmd *cmd, t_list *env_list)
{

    int i;
    int result;
    char *built_in_list[7] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    // 빌트인 함수인지를 검증한다.
    i = 0;
    while (i < 7)
    {
        result = ft_cmpstr(cmd->arg[0], built_in_list[i]);
        if (!result)
        {
            execve_cmd_bult_in(built_in_list[i], cmd, env_list);
            return (0);
        }
        i++;
    }
    return (-1);
}

int check_cmd(t_cmd *cmd, t_list *env_list)
{

    struct stat sb;
    int result;
    char *full_path;
    char **path;

    path = ft_split(get_value(env_list, "PATH"), ':');
    // 빌드인 함수의 리스트와 하나도 일치하지 않는다.
    // 내장 명령어를 검증한다.
    // 내장 명령어가 절대 주소인지, 상대 주소인지를 모두 고려해야만 한다.
    // 이차원 배열로 PATH 환경변수를 쪼개줄 것.
    if (!stat(cmd->arg[0], &sb))
    {
        execve_cmd_normal(cmd->arg[0], cmd, env_list);
        return (0);
    }
    // 절대 주소가 아니기에 PATH와 합쳐서 하나하나 대입해본다.
    while (*path) // 이차원 배열이나 연결리스트
    {
        full_path = ft_strjoin_path(*path, cmd->arg[0]);
        result = stat(full_path, &sb);
        if (!result)
        {
            execve_cmd_normal(full_path, cmd, env_list);
            return (0);
        }
        path++;
    }

    // $PATH
    // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
    // : 를 기준으로 나눠서 검증해야 한다.
    return (-1);
}

void execve_cmd(t_cmd *cmd, t_list *env_list)
{
    int result;

    result = check_bulit_in(cmd, env_list);
    if (result == -1)
    {
        result = check_cmd(cmd, env_list);
    }
    if (result == -1)
    {
        ft_error(cmd->arg[0], NULL, "command not found");
        exit(-1);
        // 상태코드 127
    }

    exit(0);
}
