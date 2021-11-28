/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:47:39 by nasong            #+#    #+#             */
/*   Updated: 2021/11/28 15:32:19 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char    *ft_strndup(char *str, int size)
{
    char *new_str;
    int index;

    index = 0;
    new_str = (char *)malloc(sizeof(char) * size);
    while (str[index] != '\0' && index < size)
    {
        new_str[index] = str[index];
        index++;
    }
    new_str[index] = '\0';
    return (new_str);
}

int quotes_check(char *str)
{
	int s_quotes;
	int d_quotes;
	int index;

	s_quotes = 0;
	d_quotes = 0;
	index = 0;

	while (str[index] != '\0')
	{
		if (str[index] == '\'')
			s_quotes++;
		else if (str[index] == '\"')
			d_quotes++;
		index++;
	}

	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
		return (-1);
	return (1);
}

int div_pipe(t_list *list, char *str)
{
	int start;
	int now_idx;

	start = 0;
	now_idx = 0;
	while(str[start] != '\0')
	{
		if (str[now_idx] != '|' && str[now_idx] != '\0')
		{
			now_idx++;
			continue;
		}
		add_data(list, ft_strndup(str + start, now_idx - start));
		start = now_idx + 1;
		now_idx = start;
	}
	return (0);
}

char *get_word(char *str)
{
	int idx;
	int quotes;

	idx = 0;
	quotes = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '\'' || str[idx] == '\"')
			quotes++;
		if (quotes == 2)
			break;
		else if (quotes == 0 && str[idx] == ' ')
			break;
		idx++;
	}
	return (ft_strndup(str, idx));
}

enum e_cmd_type get_type(char *word)
{
	return (ARG);
}

t_cmd *get_cmd(char *str)
{
	int start;
	char *word;
	t_cmd *cmd;
	enum e_cmd_type type;
	int flag_discriptor;

	start = 0;
	flag_discriptor = -1;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == 0)
		return (0);
	cmd->arg.front = 0;
	cmd->arg.size = 0;
	while (str[start] != '\0')
	{
		if (str[start] == ' ')
		{
			start++;
			continue;
		}
		word = get_word(str + start);
		type = get_type(word);
		if (type == CMD)
			cmd->cmd = word;
		else if (type == IN_DISCRIPTOR)
			flag_discriptor = 0;
		else if (type == OUT_DISCRIPTOR)
			flag_discriptor = 1;
		else //ARG
		{
			if (flag_discriptor >= 0)
			{
				cmd->discriptor[flag_discriptor] = word;
				flag_discriptor = -1;
			}
			else
				add_data(&cmd->arg, word);
		}
		start += ft_strlen(word);
	}
	return (cmd);
}

int ft_parser(t_list *cmd_list, char *input)
{
	t_list split_pipe;
	t_data *now;

	split_pipe.front = 0;
	split_pipe.size = 0;
	cmd_list->front = 0;
	cmd_list->size = 0;

	if (quotes_check(input) == -1)
		return (-1);
	printf("QUOTES TEST : OK\n");	
	div_pipe(&split_pipe, input);
	print_str_list(&split_pipe);

	now = split_pipe.front;
	while (now != 0 && now->contents != 0)
	{
		add_data(cmd_list, get_cmd(now->contents));
		now = now->next;
	}

	print_cmd_list(cmd_list);

	free_str_list(&split_pipe);
	free_cmd_list(cmd_list);
	return (0);
}
