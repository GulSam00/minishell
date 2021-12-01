#include "src/minishell.h"

int do_child(int i, int input, int output)
{
    char buf[10];
    if (i == 0)
    {
        buf[0] = 'h';
        buf[1] = 'e';
        buf[2] = 'l';
        buf[3] = 'l';
        buf[4] = 'o';
        buf[5] = '!';
        buf[6] = '\0';
    }
    if (input != -1)
    {
        dup2(input, STDIN_FILENO);
        close(input);
        read(STDIN_FILENO, buf, 6);
    }
    if (output != -1)
    {
        dup2(output, STDOUT_FILENO);
        close(output);
    }
    write(STDOUT_FILENO, buf, 6);
    exit(-1);
}
int main(void)
{
    pid_t pid;
    int fd[2];
    int prev_input = -1;
    int i = 0;
    while (i < 5)
    {
        pipe(fd);
        // printf ("pipe %d : %d %d\n", i, fd[0], fd[1]);
        pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                close(fd[0]);
                do_child(i, -1, fd[PIPE_WRITE]);
            }
            else if (i == 4)
            {

                close(fd[1]);
                do_child(i, prev_input, -1);
            }
            else
            {
                do_child(i, prev_input, fd[PIPE_WRITE]);   

            }
        }
       
        prev_input = fd[PIPE_READ];
        i++;
    }
    return (0);
}