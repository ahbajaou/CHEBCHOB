

#include "../../minishell.h"

void    print_echo(char **str,int i,int flag)
{
    char *tmp;
    tmp = NULL;
    while (str[i])
    {
        tmp = ft_join2(tmp,str[i]);
        if (str[i + 1] != NULL)
            tmp = ft_join2(tmp, " ");

        i++;
    }
    printf("%s",tmp);
    free(tmp);
    if (flag == 1)
        printf("\n");
}
int handel_n(char **str)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 0;

    flag = 1;
    while (str[i])
    {
        j = 0;
        if (str[i][0] == '-' && str[i][1] != 'n')
        {
             print_echo(str,i,flag);
            return (0);
        }
        if ((j == 0 && str[i][j] != '-'))
        {
            print_echo(str,i,flag);
            return (0);
        }
        j++;
        while (str[i][j] == 'n')
            j++;
        if (str[i][j] != 'n' || str[i][j] != 0)
            flag = 0;
        if (str[i + 1] == NULL)
            flag = 0;
        i++;
    }
    return (1);
}
void ft_echo(t_cmd *cmd, ev_list *env) 
{
    (void)env;
        if (handel_n(cmd->args) != 1)
            perror("echo");
}
