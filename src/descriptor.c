#include "minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO
extern char **environ;
// <, <<, >, >> 별로 따로따로 만들어놓기?
int ft_heardoc(char *dst)
{
    char buf[10];
    int read_buf;
    write(1, "heredoc> ", 10);
    while (buf[0] != 'c')
    {
        read_buf = read(0, buf, 9);
        buf[read_buf] = '\0';
        write(STDOUT_FILENO, buf, read_buf);
    }
    return (0);
}

int init_discriptor(char **discriptor, int *option)
{
    int temp;

    if (discriptor[1] != NULL)
    {
        if (option[1])
            temp = open(discriptor[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
        else
            temp = open(discriptor[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dup2(temp, STDOUT_FILENO) == -1)
            return (-1);
        close(temp);
    }
    if (discriptor[0] != NULL)
    {
        if (option[0])
            temp = ft_heardoc("cancel");
        else
        {
            temp = open(discriptor[0], O_RDONLY);
            if (dup2(temp, STDIN_FILENO) == -1)
                return (-1);
            close(temp);
        }
    }

    return (0);
}

int descriptor(t_cmd *cmd)
{
    if (init_discriptor(cmd->discriptor, cmd->option))
    {
        printf("error!\n");
        return -1;
    }
    char *temp[3];
    temp[0] = "cat";
    temp[1] = NULL;
    execve("/bin/cat", temp, environ);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_cmd *tmp;
    char discriptor[2];

    tmp = (t_cmd *)malloc(sizeof(t_cmd));

    tmp->discriptor[0] = "environ.txt";
    tmp->discriptor[1] = "qwer.txt";
    tmp->option[0] = 1;
    tmp->option[1] = 0;

    descriptor(tmp);
    printf("끝!\n");
    return (0);
}