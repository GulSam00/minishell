#include "minishell.h"

// unistd.h에 매크로 상수로 저장되어 있는 STDIN_FILENO, STDOUT_FILENO,STDERR_FILENO

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

int main(void)
{
    descriptor_input();
    return (0);
    /*
        int fd[2];

    pipe(fd);

    pid_t pid = fork();
    if (pid == 0) {

    }
    */
}