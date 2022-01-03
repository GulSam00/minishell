/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasong <nasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:51:39 by nasong            #+#    #+#             */
/*   Updated: 2022/01/02 14:51:41 by nasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void	append_str(t_list *word_list, char *str)
{
	t_data	*now;
	char	*target;
	char	*temp;

	target = 0;
	now = word_list->front;
	while (now->next != 0)
		now = now->next;
	target = now->contents;
	temp = ft_strjoin(target, str);
	free(now->contents);
	now->contents = temp;
}

void	append_cmd(t_list *word_list, char *word, int *add)
{
	if (*add == 0)
		add_data(word_list, word);
	else
	{
		append_str(word_list, word);
		free(word);
	}
	*add = 1;
}

int	ft_div_input(t_list *word_list, char *input, t_list *env_list)
{
	int		now;
	char	*word;
	char	*result;
	int		add;

	now = 0;
	word = 0;
	add = 0;
	while (input[now] != '\0')
	{
		if (input[now] == ' ')
		{
			add = 0;
			now++;
			continue ;
		}
		word = get_word(input + now);
		now += ft_strlen(word);
		result = check_quotes(word, env_list, 0, 0);
		free(word);
		word = result;
		result = 0;
		append_cmd(word_list, word, &add);
	}
	return (0);
}
