/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:53:07 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 13:36:13 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_check(char *str)
{
	int	s_quotes;
	int	d_quotes;
	int	index;

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

int	add_cmd(t_list *cmd_list, t_list *word_list)
{
	char			*copy;
	enum e_cmd_type	type;
	t_cmd			*new_cmd;
	t_data			*now_word;
	t_discriptor	*new_discriptor;

	new_cmd = 0;
	now_word = word_list->front;
	new_discriptor = 0;
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
			new_discriptor = (t_discriptor *)malloc(sizeof(t_discriptor));
			if (new_discriptor == 0)
				return (-1);
			init_discriptor(new_discriptor, 0, get_discriptor_type(copy));
			free(copy);
		}
		else
		{
			if (new_discriptor != 0)
			{
				new_discriptor->file_name = copy;
				add_data(&new_cmd->discriptor, new_discriptor);
				new_discriptor = 0;
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

int	ft_parser(t_list *cmd_list, char *input, t_list *env_list)
{
	t_list	word_list;

	init_list(cmd_list);
	init_list(&word_list);
	if (quotes_check(input) == -1)
		return (-1);
	if (ft_div_input(&word_list, input, env_list) == -1)
	{
		free_str_list(&word_list);
		return (-1);
	}
	add_cmd(cmd_list, &word_list);
	free_str_list(&word_list);
	return (0);
}
