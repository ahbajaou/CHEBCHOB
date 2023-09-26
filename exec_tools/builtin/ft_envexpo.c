
#include "../../minishell.h"

void print_env(ev_list **env, int flag)
{
    ev_list *tmp;

    tmp = *env;
    (void)flag;

    while (tmp)
    {
        if (flag == 1 && tmp->key != NULL && tmp->value == NULL)
        {
            printf("declare -x %s\n", tmp->key);
            // return ;
        }
        if (flag == 0 && tmp->key != NULL && tmp->value != NULL)
        {
            printf("%s=\"%s\"\n", tmp->key, tmp->value);
            // return ;
        }
        if (flag == 1 && tmp->key != NULL && tmp->value != NULL)
        {
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            // return ;
        }
        tmp = tmp->next;
    }
    free(tmp);
    return ;
}

void delet_expo(ev_list **env, char *key,char *value)
{
    ev_list *tmp;

    tmp = *env;
    (void)value;
    ev_list *perv;
    perv = NULL;
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
    free(tmp);
    return ;

}
int    checkjoin(char *key)
{
    int i = 0;
    while (key[i])
    {
        if (key[i] == '+')
            return (1);
        i++;
    }
    return (0);
}
int check_double(ev_list **env, char *key, char *value)
{

    ev_list *tmp;
    tmp = *env;
    while (tmp)
    {   
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) && ft_strcmp(tmp->value, "NULL") != 0)
        {
            if (!value)
                return (0);
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
    free(tmp);
    return (1);
}

char *skipeq(char *str,char sep)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            {
                i++;
                return (str + i);
            }
        i++;
    }
    return (str);
}
int    checkexpo(char *key,char *value,ev_list **env)
{
    ev_list *tmp;
    tmp = *env;
    char *j;
    while (tmp)
    {
        if (ft_strcmp(tmp->key,key) == 0 && ft_strcmp(tmp->value,value) != 0)
        {
            if (*value == 0)
                return (0);
            j = ft_join2(tmp->value,value);
            delet_expo(env, key, value);
            addback(env, key_value(key, j));
            free(j);
            return (0);
        }
        tmp = tmp->next;
    }
    // free(j);
    free(tmp);
    return (1);
}
char *parsq(char *value)
{
    if (!value)
        return (NULL);
    if (value[0] == '"' || value[0] == '\'')
    {
        int sz = ft_len(value) ;
        value[sz - 1] = '\0';
        return (value + 1);
    }
    return (value);
}
void expo_pars(char *str,char *str1,ev_list **env)
{
    char *value;
    if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
    || str[0] == '"' || str[0] == '\'')
    {
        printf("export : not a valid identifier : %s\n",str);
        return ;
    }
    value = parsq(str1);
    if (checkjoin(str) == 1)
    {
        int sz = ft_len(str);
        str[sz - 1] = '\0';
        if (checkexpo(str,value,env) == 0)
            return ;
    }
    addback(env, key_value(str, value));
    return ;
}
char   *joinexpo(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] == '=')
            return (skipeq(str + i,'='));
        if (str[i] == '=')
            return(skipeq(str + i, '='));
        i++;
    }
    return (NULL);
}
void add_expo(char **str, ev_list **env)
{
    int i;
    char **tmp;

    i = 0;
    (void)env;
    char *pl;
    tmp = NULL;
    
    if (str[i][0] == '=')
    {
        printf("export : not a valid identifier : %s\n",str[i]);
        free4free(str);
        free(str);
        return ;
    }
    while (str[i])
    {
        pl = joinexpo(str[i]);
        tmp = ft_split(str[i], '=');
        if (check_double(env, tmp[0], pl))
            expo_pars(tmp[0], pl,env);
        i++;
    }
    free4free(tmp);
    free(tmp);
}
void ft_env(ev_list *env, t_cmd *cmd)
{
    int flag;

    flag = -1;
    if (ft_strcmp(cmd->name, "export") == 0 && !cmd->Expo[0])
        flag = 1;
    if (ft_strcmp(cmd->name, "env") == 0)
        flag = 0;
    if (flag == -1)
    {
        add_expo(cmd->Expo, &env);
        return ;
    }
    if (flag == 0 || flag == 1)
    {
        print_env(&env, flag);
        return ;
    }
}