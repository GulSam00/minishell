/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:47:18 by marvin            #+#    #+#             */
/*   Updated: 2021/12/26 19:47:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sc;

void    check_quotes_sub(char *str, int index, int *quotes, int *rm_quotes)
{
    if (str[index] == '\'')
    {
    	if (*quotes == 0)
	    	*quotes = 1;
	    else if (*quotes == 1)
			*quotes = 0;
		*rm_quotes = 1;
	}
	else if (str[index] == '\"')
	{
		if (*quotes == 0)
			*quotes = 2;
		else if (*quotes == 2)
			*quotes = 0;
		*rm_quotes = 1;
	}
}

char	*check_quotes(char *str, t_list *env_list, int quotes, int rm_quotes)
{
	char	*result;
	char	*temp;
	int		start;
	int		end;

	result = ft_strdup(str);
	start = 0;
	end = 0;
	while (result[end] != '\0')
	{
        check_quotes_sub(result, end, &quotes, &rm_quotes);
		if (result[end] == '$' && quotes != 1)
		{
			start = end;
			temp = change_to_env(result, env_list, end);
			free(result);
			result = temp;
		}
		end++;
	}
	if (rm_quotes == 1)
	{
		temp = ft_strndup(result + 1, ft_strlen(result) - 2);
		free(result);
		result = temp;
	}
	return (result);
}

void    append_str(t_list *word_list, char *str)
{
    t_data *now;
    char *target;
    char *temp;

    target = 0;
    now = word_list->front;
    while (now->next != 0)
        now = now->next;
    target = now->contents;
    temp = ft_strjoin(target, str);
    free(now->contents);
    now->contents = temp;
}

void    append_cmd(t_list *word_list, char *word, int add)
{
    if (add == 0)
        add_data(word_list, word);
    else
    {
        append_str(word_list, word);
        free(word);
    }
}

int		ft_div_input(t_list *word_list, char *input, t_list *env_list)
{
	int		now;
	char	*word;
	char	*result;
    int     add;

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
        append_cmd(word_list, word, add);
        add = 1;
	}
	return (0);
}
