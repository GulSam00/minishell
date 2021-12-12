#include "src/minishell.h"

extern char **environ;

int do_child(int i, int input, int output)
{
    int fd;
    char *argv[3];

    // if (i == 0)
    // {
    //     sprintf(buf, "hello!\n");
    // }
    printf("**%d**\n", i);

    // dprintf(2, "pid : %d\n", getpid());
    if (i == 0)
    {
        dup2(output, 1);
        close(output);
        argv[0] = "ls";
        argv[1] = NULL;
        execve("/bin/ls", argv, environ);
        // write(1, "aadsasd\n", 9);
        // // close(1);
    }
    else if (i == 1)
    {
        char buf[10];
        dup2(input, 0);
        close(input); // 닫지 않아도 실행은 된다?
        // read(0, buf, 9);
        // printf("%s\n", buf);
        argv[0] = "grep";
        argv[1] = "out";
        argv[2] = NULL;
        execve("/usr/bin/grep", argv, environ);
        // close(0);
    }
    exit(-1);
}
int main(void)
{
    pid_t pid;
    int fd[2];
    int prev_input = -1;
    int i = 0;
    while (i < 2)
    {

        pipe(fd);
        printf("pipe %d : %d %d\n", i, fd[0], fd[1]);
        pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                close(fd[0]);
                do_child(i, -1, fd[1]);
            }
            else if (i == 1)
            {
                close(fd[0]);
                close(fd[1]);
                do_child(i, prev_input, -1);
            }
        }
        if (prev_input != -1)
            close(prev_input);
        prev_input = fd[0];
        close(fd[1]);

        i++;
    }

    return (0);
}