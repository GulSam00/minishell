/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/11/11 19:03:37 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_getlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_pwd(void)
{
    char path[MAX_PATH];
    printf("path %s\n", getcwd(path, MAX_PATH + 1));
    printf("path %s\n", getcwd(NULL, 0));

    // if (!getcwd(path, MAX_PATH + 1))
    if (!getcwd(NULL, 0))
        return (-1);
    printf("%s\n", path);
    //free(path);
    return (0);
}
int ft_chdir(char *cmd)
{
    /*
    char *path;
    path = getcwd(NULL, 0);
    printf("before path : %s\n", path);
    printf("Result : %d\n", chdir(cmd));
    path = getcwd(NULL, 0);
    printf("after path : %s\n", path);
    */
    if (!chdir(cmd))
        return (-1);
    return (0);
}

void ft_echo(int fd, int option, char *cmd)
{
    // 임시 변편
    fd = 1;
    write(fd, cmd, ft_getlen(cmd));
    if (option)
        write(fd, "\n", 1);
}

int cmpstr(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i])
    {
        if (str1[i] != str2[i])
            return -1;
        i++;
    }
    if (str2[i])
        return -1;
    return 0;
}

void check_command(char *str)
{
    if (!cmpstr("pwd", str))
        ft_pwd();
    else if (!cmpstr("cd", str))
        ft_chdir("..");
    else if (!cmpstr("echo", str))
        ft_echo(1, 0, "test");
}

int main(void)
{

    /* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
    char *str;
    /* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
    while (1)
    {
        /* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
        str = readline("nanoshell$ "); /* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        if (str)                       /* 입력이 된다면 (주소가 존재한다면) */
            printf("%s\n", str);       /* 주소안에 문자열을 출력해보자 */
        else                           /* str = NULL 이라면 (EOF, cntl + D)*/
            break;                     /* 반복문을 탈출해준다.*/
        check_command(str);            /* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
        add_history(str);
        /* 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
        free(str);
    }
    /* 함수종료 */
    return (0);
}
