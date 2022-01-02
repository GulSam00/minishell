#include "../minishell.h"

extern int g_sc;

void    first_quotes_check(char *str, int *index, int *first_quotes)
{
    *index = 0;
    *first_quotes = 0;
    if (str[*index] != '\'' && str[*index] != '\"')
        return ;
    if (str[*index] == '\'')
		*first_quotes = 1;
	else if (str[*index] == '\"')
		*first_quotes = 2;
    *index += 1;
}

char	*get_word(char *str)
{
	int	idx;
	int	first_quotes;

    first_quotes_check(str, &idx, &first_quotes);
	while (str[idx] != '\0')
	{
		if (str[idx] == '\'')
		{
			if (first_quotes == 1)
				idx++;
			if (first_quotes != 2)
				break ;
		}
		else if (str[idx] == '\"')
		{
			if (first_quotes == 2)
				idx++;
			if (first_quotes != 1)
				break ;
		}
		if (str[idx] == ' ' && first_quotes == 0)
			break ;
		idx++;
	}
	return (ft_strndup(str, idx));
}

