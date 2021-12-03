#include "src/minishell.h"

int do_child(int i, int input, int output)
{
    char buf[10];
    if (i == 0)
    {
        sprintf(buf, "hello!\n"); 
    }
    printf ("**%d**\n", i);
    if (i == 3) // 4번째 자식 프로세스에서 3초간 멈추었다가 진행한다.
    {
        printf ("stop!\n");
        sleep(3);
        printf ("stop end\n");
    }
    if (input != -1)
    {
        dup2(input, STDIN_FILENO);
        close(input); // 닫지 않아도 실행은 된다?
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
    pid_t special_pid;
    int fd[2];
    int prev_input = -1;
    int i = 0;
    while (i < 5)
    {
      
        pipe(fd);
        printf("%d %d\n", fd[0], fd[1]);
        // printf ("pipe %d : %d %d\n", i, fd[0], fd[1]);
        pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                close(fd[0]);
                do_child(i, -1, fd[1]);
            }
            else if (i == 4)
            {

                close(fd[1]);
                do_child(i, prev_input, -1);
            }
            else
            {
                do_child(i, prev_input, fd[1]);   
            }
        }
       
        special_pid = pid;
        prev_input = fd[0];    
        i++;
    }
    waitpid(special_pid, &i, 0);
    return (0);
}