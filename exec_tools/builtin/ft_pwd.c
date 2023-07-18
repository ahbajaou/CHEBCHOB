

#include "../../minishell.h"

void ft_pwd(void)
{
    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    return;
}
