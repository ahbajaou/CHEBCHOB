#include "../../minishell.h"

void	ft_pwd(ev_list *env)
{
	ev_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			printf("%s\n", tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
	free(tmp);
	tmp = NULL;
	return ;
}
