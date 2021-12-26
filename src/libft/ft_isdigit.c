#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= (int) '0' && c <= (int) '9')
		return (1);
	return (0);
}
