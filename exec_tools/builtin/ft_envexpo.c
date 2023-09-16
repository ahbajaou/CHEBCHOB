
#include "../../minishell.h"



char *get_sub(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            i++;
            return (str + i);
        }
        i++;
    }
    return (str);
}
void print_env(ev_list **env, int flag)
{
    ev_list *tmp;

    tmp = *env;
    (void)flag;

    while (tmp)
    {
        if (flag == 1 && tmp->key != NULL && tmp->value == NULL)
            printf("declare -x %s\n", tmp->key);
        if (flag == 0 && tmp->key != NULL && tmp->value != NULL)
            printf("%s=%s\n", tmp->key, tmp->value);
        if (flag == 1 && tmp->key != NULL && tmp->value != NULL)
            printf("declare -x %s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    free(tmp);
}

void delet_expo(ev_list **env, char *key,char *value)
{
    ev_list *tmp;

    tmp = *env;
    (void)value;
    ev_list *perv;
    if (env != NULL)
    {
        if (tmp->key != key)
        {
            while (tmp->next != NULL)
            {
                if (ft_strcmp(tmp->next->key, key) == 0)
                {
                    perv = tmp->next;
                    tmp->next = tmp->next->next;
                    free(perv);
                    return ;
                }
                tmp = tmp->next;
            }
        }
    }

}
int check_double(ev_list **env, char *key, char *value)
{

    ev_list *tmp;
    tmp = *env;
    while (tmp)
    {   
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value))
        {
            delet_expo(env, key, value);
            addback(env, key_value(key, value));
            return (0);
        }
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
            return (0);
        if (ft_strcmp(tmp->key, key) == 0 && value == NULL)
            return (0);
        tmp = tmp->next;
    }
    return (1);
}
void expo_pars(char *str,char *str1,ev_list **env)
{
    int i = 0;
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        {
            printf("export: `%s=%s': not a valid identifier\n",str, str1);
            return ;
        }
        i++;
    }
    addback(env, key_value(str, str1));
}
void add_expo(char **str, ev_list **env)
{
    int i;
    char **tmp;

    i = 0;
    tmp = NULL;
    while (str[i])
    {
        tmp = ft_split(str[i], '=');
        if (check_double(env, tmp[0], get_sub(str[i])))
            expo_pars(tmp[0], get_sub(str[i]),env);
        i++;
    }
    free(tmp);
}
void ft_env(ev_list *env, t_cmd *cmd)
{
    int flag;

    flag = -1;

    if (ft_strcmp(cmd->name, "export") == 0 && !cmd->args[0])
        flag = 1;
    if (ft_strcmp(cmd->name, "env") == 0)
        flag = 0;
    if (flag == -1)
        add_expo(cmd->args, &env);
    if (flag == 0 || flag == 1)
        print_env(&env, flag);
}