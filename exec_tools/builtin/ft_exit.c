
#include "../../minishell.h"

void ft_exit(t_cmd *cmd)
{
	int i = 0;
	// int j = 0;
	// int m = 0;
	while (cmd->args[i])
	{

		if (((cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z') && i == 0 ) || ((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') && i == 0))
		{
			printf("exit: %s: numeric argument required\n",cmd->args[i]);
			return ;

		}
		// while (cmd->args[i][j])
		// {
		// 	if (cmd->args[i][j] == '-')
		// 	{
		// 			m++;
		// 			break;
		// 	}
		// 	printf("----%d----\n",m);
		// 	if (m > 1)
		// 	{
		// 		printf("exit: %s: numeric argument required\n",cmd->args[i]);
		// 			return ;
		// 	}
		// 	j++;
		// }
		i++;
	}
	if (i > 1)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	return ;
}