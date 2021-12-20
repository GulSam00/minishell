#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_replace_line("", 6);
    // rl_on_new_line();

    // rl_redisplay();
}

int main(void)
{
    int ret;
    char *line;
    int i = 0;
    int sb;
    signal(SIGINT, handler);

    while (1)
    {
        line = readline("input> ");
        if (line)
        {
            if (ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("ctrl + d\n");
        }
        i++;
    }
    return (0);
}