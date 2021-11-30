#include "minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO
extern char **environ;

int ft_d_right_paste(char *dst)
{
    int temp;
    temp = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp == -1)
        return (-1);

    if (dup2(temp, STDOUT_FILENO) == -1) // 에러?
        return (-1);
    return (close(temp));
}

int ft_d_right_append(char *dst)
{
    int temp;

    temp = open(dst, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (temp == -1)
        return (-1);
    if (dup2(temp, STDOUT_FILENO) == -1)
        return (-1);
    return (close(temp));
}

int ft_d_left_normal(char *dst)
{
    int temp;
    temp = open(dst, O_RDONLY);
    if (dup2(temp, STDIN_FILENO) == -1)
        return (-1);
    return (close(temp));
}

int ft_d_left_heredoc(char *dst)
{
    char *buf;
    while (1)
    {
        buf = get_next_line();
        if (ft_cmpstr(dst, buf) == 0)
            break;
    }
    return (0);
}

int route_d(char *discriptor, char *dst)
{

    if (ft_cmpstr(discriptor, ">") == 0)
        ft_d_right_paste(dst);
    else if (ft_cmpstr(discriptor, ">>") == 0)
        ft_d_right_append(dst);
    else if (ft_cmpstr(discriptor, "<") == 0)
        ft_d_left_normal(dst);
    else if (ft_cmpstr(discriptor, "<<") == 0)
        ft_d_left_heredoc(dst);
    else
    {
        printf("no match!\n");
        return (-1);
    }
    return (0);
}

int check_builtin(t_cmd *cmd, t_env *ft_env)
{
    
}

int init_descriptor(t_cmd *cmd, t_env *ft_env)
{
    int code;
    pid_t pid;
    while (cmd->next)
    {
        code = check_builtin(cmd, ft_env);
        cmd = cmd->next;
    }
 // $PATH
 // /Users/sham/.brew/bin:/Users/sham/.brew/bin:/Users/sham/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
 // : 를 기준으로 나눠서 검증해야 한다.
     pid = fork();

    if (pid > 0)
    { // 부모 코드
        printf("부모코드\n");
    }
    else if (pid == 0)
    { // 자식 코드
       
        execve("/bin/cat", temp, environ);
        exit(0);
    }
    else
    { // fork 실패
        printf("fork Fail! \n");
        return -1;
    }

    return (0);
}

int main(int argc, char **argv, char **envp)
{
    char *str;
    // 환경변수
    while (1)
    {
        str = readline("nanoshell$ "); 
        init_descriptor();
        add_history(str);

        free(str);
    }
    /* 함수종료 */
    return (0);
}