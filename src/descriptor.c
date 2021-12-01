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

int init_descriptor(t_dis *dis)
{
    while (dis->next)
    {
        if (!ft_cmpstr(dis->type, ">"))
            ft_d_right_paste(dis->dst);
        else if (!ft_cmpstr(dis->type, ">>"))
            ft_d_right_append(dis->dst);
        else if (!ft_cmpstr(dis->type, "<"))
            ft_d_left_normal(dis->dst);
        else if (!ft_cmpstr(dis->type, "<<"))
            ft_d_left_heredoc(dis->dst);
        else
    {
        ft_error_message("no match!\n");
        return (-1);
    }
    }

    return (0);
}
