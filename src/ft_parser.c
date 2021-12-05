/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:47:39 by nasong            #+#    #+#             */
/*   Updated: 2021/12/05 18:52:41 by nasong           ###   ########.fr       */
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

char *get_word(char *str)
{
	int idx;
	int quotes;

	idx = 0;
	quotes = 0;
	if (str[idx] == '\'' || str[idx] == '\"')
	{
		quotes = 1;
		idx++;
	}
	while (str[idx] != '\0')
	{
		if (str[idx] == '\'' || str[idx] == '\"')
		{
			if (quotes > 0)
				idx++;
			break;
		}
		if (str[idx] == ' ')
			break;
		idx++;
	}
	return (ft_strndup(str, idx));
}

enum e_cmd_type get_type(char *word)
{
	int len;

	len = ft_strlen(word);
	if (len == 1 && word[0] == '|')
		return (PIPE);
	return (ARG);
}

int	div_input(t_list *word_list, char *input)
{
	int now;
	char *word;

	now = 0;
	word = 0;
	while (input[now] != '\0')
	{
		if (input[now] == ' ')
		{
			now++;
			continue;
		}
		word = get_word(input + now);
		if (word == 0)
			return (-1);
		now += ft_strlen(word);
		add_data(word_list, word);
	}
	return (0);
}

int add_cmd(t_list *cmd_list, t_list *word_list)
{
	t_data *now_word;
	char *copy;
	t_list arg;
	enum e_cmd_type type;
	t_cmd *new_cmd;

	arg.front = 0;
	arg.size = 0;
	new_cmd = 0;
	now_word = word_list->front;
	while (now_word != 0)
	{
		if (new_cmd == 0)
		{
			new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (new_cmd == 0)
				return (-1);
			new_cmd->arg.front = 0;
			new_cmd->arg.size = 0;
			new_cmd->discriptor.front = 0;
			new_cmd->discriptor.size = 0;
		}
		type = get_type(now_word->contents);
		copy = ft_strndup(now_word->contents, ft_strlen(now_word->contents));
		if (type == PIPE)
		{
			add_data(cmd_list, new_cmd);
			new_cmd = 0;
		}
		else if (type == CMD)
		{
			new_cmd->cmd = copy;
		}
		else //ARG
		{
			add_data(&new_cmd->arg, copy);
		}
		now_word = now_word->next;
	}
	if (new_cmd != 0)
		add_data(cmd_list, new_cmd);
	return (0);
}

int ft_parser(t_list *cmd_list, char *input)
{
	t_list word_list;

	cmd_list->front = 0;
	cmd_list->size = 0;
	word_list.front = 0;
	word_list.size = 0;
	if (quotes_check(input) == -1)
		return (-1);
	printf("QUOTES TEST : OK\n");	

	if (div_input(&word_list, input) == -1)
	{
		free_str_list(&word_list);
		return (-1);
	}
	print_str_list(&word_list);

	add_cmd(cmd_list, &word_list);
	free_str_list(&word_list);
	print_cmd_list(cmd_list);

	free_cmd_list(cmd_list);
	return (0);
}
