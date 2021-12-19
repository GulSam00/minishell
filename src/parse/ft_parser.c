/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:53:07 by nasong            #+#    #+#             */
/*   Updated: 2021/12/12 15:11:52 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[idx] == ' ' && quotes == 0)
			break;
		idx++;
	}
	return (ft_strndup(str, idx));
}

int div_input(t_list *word_list, char *input)
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

char **list_to_char(t_list *str_list)
{
	char **result;
	t_data *now_data;
	int index;

	result = (char **)malloc(sizeof(char *) * (str_list->size + 1));
	if (result == 0)
		return (0);
	now_data = str_list->front;
	index = 0;
	while (now_data != 0)
	{
		result[index] = ft_strdup(now_data->contents);
		now_data = now_data->next;
		index++;
	}
	result[index] = 0;
	return (result);
}

int add_cmd(t_list *cmd_list, t_list *word_list)
{
	char *copy;
	enum e_cmd_type type;
	t_cmd *new_cmd;
	t_data *now_word;
    char *discriptor;
    t_discriptor *new_discriptor;

	new_cmd = 0;
	now_word = word_list->front;
    discriptor = 0;
	while (now_word != 0)
	{
		if (new_cmd == 0)
		{
			new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (new_cmd == 0)
				return (-1);
			init_cmd(new_cmd);
		}
		type = get_type(now_word->contents);
		copy = ft_strndup(now_word->contents, ft_strlen(now_word->contents));
		if (type == PIPE)
		{
			new_cmd->arg = list_to_char(&new_cmd->arg_list);
			add_data(cmd_list, new_cmd);
			new_cmd = 0;
		}
        else if (type == DISCRIPTOR)
        {
            discriptor = copy;
        }
		else //ARG
		{
            if (discriptor != 0)
            {
                new_discriptor = (t_discriptor *)malloc(sizeof(t_discriptor));
                if (new_discriptor == 0)
                    return (-1);
                init_discriptor(new_discriptor, copy, IN);
                discriptor = 0;
                add_data(&new_cmd->discriptor, new_discriptor);
            }
            else
			    add_data(&new_cmd->arg_list, copy);
		}
		now_word = now_word->next;
	}
	if (new_cmd != 0)
	{
		new_cmd->arg = list_to_char(&new_cmd->arg_list);
		add_data(cmd_list, new_cmd);
	}
	return (0);
}

int ft_parser(t_list *cmd_list, char *input)
{
	t_list word_list;

	init_list(cmd_list);
	init_list(&word_list);
	if (quotes_check(input) == -1)
		return (-1);
	printf("QUOTES TEST : OK\n");

	if (div_input(&word_list, input) == -1)
	{
		free_str_list(&word_list);
		return (-1);
	}
	add_cmd(cmd_list, &word_list);
	free_str_list(&word_list);
	print_cmd_list(cmd_list);
	return (0);
}
