/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:53:07 by nasong            #+#    #+#             */
/*   Updated: 2021/12/06 11:03:23 by sham             ###   ########.fr       */
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

char *list_to_char(t_list *list)
{
	char *result;
	char *temp;
	t_data *now_data;

	now_data = list->front;
	result = ft_strndup(now_data->contents, ft_strlen(now_data->contents));
	now_data = now_data->next;
	while (now_data != 0)
	{
		temp = ft_strjoin(result, " ");
		free(result);
		result= temp;
		temp = ft_strjoin(result, now_data->contents);
		free(result);
		result = temp;
		now_data = now_data->next;
	}
	return (result);
}


int add_cmd(t_list *cmd_list, t_list *word_list)
{
	char *copy;
	enum e_cmd_type type;
	t_cmd *new_cmd;
	t_data *now_word;

	new_cmd = 0;
	now_word = word_list->front;
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
		else if (type == CMD)
		{
			new_cmd->cmd = copy;
		}
		else //ARG
		{
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

int main(int argc, char **argv)
{
	t_list *list;
	list = malloc(sizeof(t_list));
	ft_parser(list, argv[1]);
	return (0);
}