/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:52:30 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 17:27:56 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_check(char *str)
{
	int	quotes[2];
	int	index;
    int q_index;

	quotes[0] = 0;
	quotes[1] = 0;
	index = 0;
    q_index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\'')
        {
            if (q_index > 0 &&quotes[q_index - 1] == 1)
                quotes[--q_index] = 0;
            else
            {
                if (q_index >= 2)
                    return (-1);
                quotes[q_index++] = 1;
            }
        }
		else if (str[index] == '\"')
        {
            if (q_index > 0 &&quotes[q_index - 1] == 2)
                quotes[--q_index] = 0;
            else
            {
                if (q_index >= 2)
                    return (-1);
                quotes[q_index++] = 2;
            }
        }
		index++;
	}
	if (q_index != 0)
		return (-1);
	return (1);
}

void	set_next_cmd(t_list *cmd_list, t_cmd **new_cmd)
{
	t_cmd	*cmd;

	cmd = *new_cmd;
	cmd->arg = list_to_char(&(cmd->arg_list));
	add_data(cmd_list, cmd);
	*new_cmd = 0;
}

void	set_cmd(t_list *cmd_list, t_discriptor **new_discriptor, \
		t_data *now_word, t_cmd **new_cmd)
{
	char			*copy;
	t_cmd			*cmd;

	cmd = *new_cmd;
	copy = ft_strndup(now_word->contents, ft_strlen(now_word->contents) + 1);
	if (get_type(now_word->contents) == PIPE)
		set_next_cmd(cmd_list, new_cmd);
	else if (get_type(now_word->contents) == DISCRIPTOR)
	{
		*new_discriptor = (t_discriptor *)malloc(sizeof(t_discriptor));
		init_discriptor(*new_discriptor, 0, get_discriptor_type(copy));
		free(copy);
	}
	else
	{
		if (*new_discriptor != 0)
		{
			(*new_discriptor)->file_name = copy;
			add_data(&(cmd->discriptor), *new_discriptor);
			*new_discriptor = 0;
		}
		else
			add_data(&(cmd->arg_list), copy);
	}
}

int	add_cmd(t_list *cmd_list, t_list *word_list)
{
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
			init_cmd(new_cmd);
		}
		set_cmd(cmd_list, &new_discriptor, now_word, &new_cmd);
		now_word = now_word->next;
	}
	if (new_cmd != 0)
		set_next_cmd(cmd_list, &new_cmd);
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
	if (word_list.size == 0)
		return (-1);
	add_cmd(cmd_list, &word_list);
	free_str_list(&word_list);
	return (0);
}
