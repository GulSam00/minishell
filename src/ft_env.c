#include "minishell.h"

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return (len);
}

char    *ft_strdup(char *str)
{
    char *new_str;
    int len;
    int index;

    index = 0;
    len = ft_strlen(str);
    new_str = (char *)malloc(sizeof(char) * len);
    while (index < len)
    {
        new_str[index] = str[index];
        index++;
    }
    new_str[index] = '\0';
    return (new_str);
}

int     ft_strncmp(char *str1, char *str2, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (str1[i] == '\0' || str2[i] == '\0')
            break;
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
}

void    test_env()
{
    t_env_list env_list;

    env_list.size = 0;
    env_list.front = 0;
    ft_export(&env_list, "test_key1", "test_value1");
    ft_export(&env_list, "test_key2", "test_value2");
    ft_env(&env_list);
    ft_unset(&env_list, "test_key1");
    ft_env(&env_list);
    free_all_envs(&env_list);
    ft_env(&env_list);
}

void    free_all_envs(t_env_list *env_list)
{
    t_env *now;
    t_env *next;

    now = env_list->front;
    while (now != 0)
    {
        next = now->next;
        free(now->key);
        free(now->value);
        now = next;
    }
    env_list->front = 0;
    env_list->size = 0;
}

void    ft_unset(t_env_list *env_list, char *key)
{
    t_env *now;
    t_env *pre;
    int key_len;
    int env_key_len;

    if (env_list == 0)
        return ;
    now = env_list->front;
    pre = 0;
    key_len = ft_strlen(key);
    while (now != 0)
    {
        env_key_len = ft_strlen(now->key);
        if ((env_key_len == key_len) && ft_strncmp(now->key, key, key_len))
        {
            if (pre == 0)
            {
                env_list->front = now->next;
                free(now->key);
                free(now->value);
            }
            else
            {
                pre->next = now->next;
                free(now->key);
                free(now->value);
                now = pre->next;
            }
            env_list->size--;
            return ;
        }
        else
        {
            pre = now;
            now = now->next;
        }
    }
}

void    ft_export(t_env_list *env_list, char *key, char *value)
{
    t_env *new;
    t_env *now;

    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = 0;
    now = env_list->front;
    if (now == 0)
    {
        env_list->front = new;
        env_list->size = 1;
    }
    else
    {
        while (now->next != 0)
        {
            now = now->next;
        }
        now->next = new;
        env_list->size++;
    }
}

void    ft_env(t_env_list *env_list)
{
    t_env *now;

    if (env_list->front == 0 || env_list->size == 0)
        return ;
    now = env_list->front;
    int i = 0;
    while (now != 0)
    {
        write(1, " ", 1);
        write(1, now->key, ft_strlen(now->key));
        write(1, "|", 1);
        write(1, now->value, ft_strlen(now->value));
        write(1, "\n", 1);
        now = now->next;
        i++;
    }
}
