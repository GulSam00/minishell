#include "minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO
extern char **environ;

void descriptor_input(void)
{
    int temp;
    char buf[100];

    temp = open("../test.txt", O_RDONLY);

    if (dup2(temp, STDIN_FILENO) == -1)
        printf("error!\n");
    close(temp);
    read(STDIN_FILENO, buf, 100);
    printf("read : %s\n", buf);
}
void descriptor_output(int flag)
{
    int temp;
    int test;

    temp = flag ? open("../test.txt", O_WRONLY | O_APPEND) : open("../test.txt", O_WRONLY);
    test = flag ? 1 : 0;
    if (dup2(temp, STDOUT_FILENO) == -1)
        printf("error!\n");
    close(temp);

    write(STDOUT_FILENO, "test\n", 5);
}




int init_discriptor(char **discriptor, int option)
{
    int temp;
    if (discriptor[0] != NULL)
    {
        temp = open(discriptor[0], O_RDONLY);
        if (dup2(temp, STDIN_FILENO) == -1)
            return (-1);
        close(temp);
    }
    if (discriptor[1] != NULL)
    {
        temp = option ? open(discriptor[1], O_WRONLY | O_APPEND | O_CREAT, 0644) : open(discriptor[1], O_WRONLY | O_CREAT, 0644);
        if (dup2(temp, STDOUT_FILENO) == -1)
        {
            printf ("%s, %d\n", discriptor[1], temp);
            return (-1);
        }
        close(temp);
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
    char* temp[3];
    temp[0] = "head";
    temp[1] = "-5";
    temp[2] = NULL;
    execve("/usr/bin/head", temp, environ);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_cmd *tmp;
    char discriptor[2];
    
    tmp = (t_cmd*)malloc(sizeof(t_cmd));

    tmp->discriptor[0] = "environ.txt";
    tmp->discriptor[1] = "qwer.txt";
    tmp->option = 0;
    
    
    descriptor(tmp);
    printf("끝!\n");
    return (0);
}