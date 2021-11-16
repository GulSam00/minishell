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

int ft_getlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    //printf("%s len : %d\n", str, i);
    return (i);
}

char *ft_cpstr(char *str)
{
    char *temp;
    int i;

    i = 0;
    temp = (char *)malloc(ft_getlen(str) + 1);
    while (str[i])
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    return temp;
}
char **parse(int argc, char *argv[])
{
    char **command_list;
    int i;

    i = 1;
    command_list = (char **)malloc(sizeof(char *) * (argc - 1));
    while (i < argc)
    {
        printf("argv[%d] : %s\n", i, argv[i]);
        command_list[i] = ft_cpstr(argv[i]);
        printf("cp success! - %s\n", command_list[i]);
        i++;
    }
    return command_list;
}

int main(int argc, char *argv[])
{
    char **command_list;
    command_list = parse(argc, argv);
    //descriptor_input();
    return (0);
    /*
        int fd[2];

    pipe(fd);

    pid_t pid = fork();
    if (pid == 0) {

    }
    */
}