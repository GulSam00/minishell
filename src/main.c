/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:09:22 by sham              #+#    #+#             */
/*   Updated: 2021/11/28 17:38:20 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_command(char *str)
{
    int result = 0;
    if (!cmpstr("pwd", str))
        result = ft_pwd();
    else if (!cmpstr("cd", str))
        result = ft_chdir("..");
    else if (!cmpstr("echo", str))
        result = ft_echo(1, 0, "test");
    return result;
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
        if (check_command(str))
            printf("error!\n"); /* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
        add_history(str);
        /* 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
        free(str);
    }
    /* 함수종료 */
    return (0);
}
