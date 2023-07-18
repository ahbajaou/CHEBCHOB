

#include "../../minishell.h"

char *ft_supstr(char *str,int start,int end)
{
    int i;
    char *new;

    i = 0;
    new = malloc(sizeof(char) * ft_len(str));
    while (start < end)
    {
        new[i] = str[start];
        i++;
        start++;
    }
    new[i] = '\0';
    return (new);
}
void    print_echo(char **str,int i,int flag)
{
    char *tmp;
    int j;

    j = 0;
    tmp = NULL;
    if (str[i][j] == '"')
    {
        char *new = ft_supstr(str[i],j + 1,ft_len(str[i]) - 1);
        // printf("--%s---\n",new);
        str[i] = new;
        // exit(0);
    }
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
        if ((j == 0 && str[i][j] != '-') || flag == 0)
        {
            // if (str[i - 1][0] == '-')
            //     flag = 0;
            print_echo(str,i,flag);
            return (0);
        }
        j++;
        while (str[i][j] == 'n')
        {
            j++;
        }
        if (str[i][j] != 'n')
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
     if (cmd->args)
     {
        if (handel_n(cmd->args) != 1)
            return ;
     }
}
