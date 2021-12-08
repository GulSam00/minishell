#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>

// gcc testsignal.c -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        //printf("\033[K"); 지워버리는 것을 원하지는 않았음.
        printf("nanoshell$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}

int main(int argc, char **argv, char **envp)
{
    char *str;
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    setting_signal();

    while (1)
    {
        str = readline("nanoshell$ ");
        if (!str)
        {
            printf("\033[1A");
            printf("\033[10C");
            printf(" exit\n");
            exit(-1);
        }
        else if (*str == '\0')
        {
            free(str);
        }
        else
        {
            add_history(str);
            printf("%s\n", str);
            free(str);
        }
    }
    /* 함수종료 */
    return (0);
}