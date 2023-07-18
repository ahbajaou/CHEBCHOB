
#include "../../minishell.h"

void ft_exit(t_cmd *cmd)
{

    if (ft_strcmp(cmd->name, "exit") == 0)
        exit(0);
}