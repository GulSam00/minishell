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

int descriptor(void)
{
    pid_t pid;
    t_cmd *tmp;

    tmp = (t_cmd *)malloc(sizeof(t_cmd));

    tmp->discriptor[0] = "environ.txt";
    tmp->discriptor[1] = "qwer.txt";
    char *temp[3];
    temp[0] = "cat";
    temp[1] = NULL;

    pid = fork();

    if (pid > 0)
    { // 부모 코드
        printf("부모코드\n");
    }
    else if (pid == 0)
    { // 자식 코드
        if (route_d(">", "text.txt"))
        {
            printf("error!\n");
            return (-1);
        }
        printf("scuccec\n");
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
    /* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
    char *str;
    /* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
    while (1)
    {
        /* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
        str = readline("nanoshell$ "); /* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        descriptor();
        add_history(str);

        /* 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
        free(str);
    }
    /* 함수종료 */
    return (0);
}