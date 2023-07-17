/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:48:51 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/17 02:44:05 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (1);
    // printf("--%s----%s---\n",s1,s2);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
int ft_len(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}
char	*ft_join(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(ft_len(s1) + ft_len(s2) + 1);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		free((char *)s1);
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
void    print_echo(char **str,int i,int flag)
{
    char *tmp;

    tmp = NULL;
    while (str[i])
    {
        tmp = ft_join(tmp,str[i]);
        if (str[i + 1] != NULL)
            tmp = ft_join(tmp, " ");
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

int is_alpha(char **str)
{
    int i;
    int j;

    i = 1;
    if (!*str || !str)
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if ((str[i][j] >= 'a' && str[i][j] <= 'z') || (str[i][j] >= 'A' && str[i][j] <= 'Z'))
            {
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
int _isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}
int str_chr(char **str)
{
    int i;
    int j;

    i = 1;
    if (!*str || !str)
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (str[i][j] == '=')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}
void print_env(ev_list *env, int flag)
{
    ev_list *tmp;

    tmp = env;
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

void delet_expo(ev_list *env, char *key,char *value)
{
    ev_list *tmp;

    tmp = env;
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
int check_double(ev_list *env, char *key, char *value)
{
    (void)env;
    (void)value;

    ev_list *tmp;
    tmp = env;
    while (tmp)
    {
            if (key != NULL && value == NULL)
                return (0);
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value))
        {
            delet_expo(env, key, value);
            addback(&env, key_value(key, value));
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
void expo_pars(char *str,char *str1,ev_list *env)
{
    int i = 0;
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        {
            printf("export: `%s=%s': not a valid identifier\n",str, str1);
            return ;
        }
        addback(&env, key_value(str, str1));
        i++;
    }
}
void add_expo(char **str, ev_list *env)
{
    int i;
    char **tmp;

    i = 1;
    tmp = NULL;
    while (str[i])
    {
        tmp = ft_split(str[i], '=');
        if (check_double(env, tmp[0], tmp[1]))
            expo_pars(tmp[0], tmp[1],env);

        i++;
    }
    free(tmp);
}
void ft_env(ev_list *env, t_cmd *cmd)
{
    int flag;

    flag = -1;

    if (ft_strcmp(cmd->name, "export") == 0)
        flag = 1;
    if (ft_strcmp(cmd->name, "env") == 0)
        flag = 0;
    if (flag == -1)
        add_expo(cmd->args, env);
    if (flag == 0 || flag == 1)
        print_env(env, flag);
}

void        delet_unset(ev_list **env,char *key)
{
    ev_list *tmp;
    ev_list *perv;

    perv = NULL;
    tmp = *env;

    if (env != NULL)
    {
        if (ft_strcmp(tmp->key, key) != 0)
        {
            while (tmp->next)
            {
                if (ft_strcmp(tmp->next->key, key) == 0)
                {
                    perv = tmp->next;
                    free(tmp->next->key);
                    free(tmp->next->value);
                    tmp->next = tmp->next->next;
                    free(perv);
                    return ;
                }
                tmp = tmp->next;
            }
        }
        else
        {
            tmp = (*env);
            (*env) = (*env)->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }

    }
}
void    ft_unset(ev_list **env, t_cmd *cmd)
{
    (void)env;
    (void)cmd;
    ev_list *tmp;
    tmp = (*env);
    int i = 1;

    while (tmp)
    {
        while (cmd->args[i])
        {
            if (ft_strcmp(cmd->args[i], tmp->key) == 0)
            {
                delet_unset(env,tmp->key);
                return ;
            }
            else
                break;
            i++;
        }
        tmp = tmp->next;
    }
    free(tmp);
}
void    ft_pwd(void)
{
    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n",cwd);
    return ;


}
void    update_path(ev_list *env, char *old,char *path,char *new)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(old, tmp->key) == 0)
            tmp->value = ft__strdup(new);
        if (ft_strcmp(path, tmp->key) == 0)
            tmp->value = ft__strdup(new);
        tmp = tmp->next;
    }
    free(tmp);
}
void    ft_cd(t_cmd *cmd, ev_list *env)
{
 
    char cwd[256];

        if (ft_strcmp("cd", cmd->name) == 0 && !cmd->args)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
            chdir("..");
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
        else
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
            chdir(cmd->args[0]);
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
 
}
void    ft_exit(t_cmd *cmd)
{

    if (ft_strcmp(cmd->name, "exit") == 0)
        exit(0);

}
int  check_builting(t_cmd *cmd, ev_list **env)
{

        if (ft_strcmp("env", cmd->name) == 0)
        {
            ft_env(*env, cmd);
            return (1);
        }
        if (ft_strcmp("export", cmd->name) == 0)
        {
            ft_env(*env, cmd);
            return (1);

        }
        if (ft_strcmp("unset", cmd->name) == 0)
        {
            ft_unset(env, cmd);
            return (1);

        }
        if (ft_strcmp("echo", cmd->name) == 0)
        {
            ft_echo(cmd,*env);
            return (1);

        }
        if (ft_strcmp("pwd", cmd->name) == 0)
        {
            ft_pwd();
            return (1);

        }
        if (ft_strcmp("cd", cmd->name) == 0)
        {
            ft_cd(cmd,*env);
            return (1);

        }
        if (ft_strcmp("exit", cmd->name) == 0)
        {
            ft_exit(cmd);
            return (1);

        }
    return (0);
}