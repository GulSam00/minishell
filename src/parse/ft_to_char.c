#include "../minishell.h"

extern int g_sc;

char	**list_to_char(t_list *str_list)
{
	char	**result;
	t_data	*now_data;
	int	index;

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

char	**env_to_char(t_list *env_list)
{
	char	**result;
	int		index;
	t_data	*now_env;
	t_env	*target;

	result = (char **)malloc(sizeof(char *) * (env_list->size + 1));
	if (result == 0)
		return (0);
	index = 0;
	now_env = env_list->front;
	while (now_env != 0)
	{
		target = now_env->contents;
		if (target->value == 0)
		{
			now_env = now_env->next;
			continue ;
		}
		result[index] = ft_strjoin_with_char(target->key, target->value, '=');
		now_env = now_env->next;
		index++;
	}
	result[index] = NULL;
	return (result);
}

