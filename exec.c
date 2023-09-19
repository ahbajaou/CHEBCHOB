/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:46:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/19 17:52:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void redir(t_cmd *cmd)
{
    int fdd;
    if (cmd->redirection == 2)
    {
        cmd->outf = open(cmd->redirection_file, O_CREAT | O_RDWR ,0644);
        dup2(cmd->outf,STDOUT_FILENO);
        close(cmd->outf);
    }
    if (cmd->redirection == 1)
    {
        cmd->inf = open(cmd->redirection_file,O_RDONLY , 0644);
        dup2(cmd->inf,STDIN_FILENO);
        close(cmd->inf);
    }
    if (cmd->redirection == 3)
    {
        fdd = open(cmd->redirection_file, O_CREAT | O_RDWR | O_APPEND , 0644);
        dup2(fdd,STDOUT_FILENO);
        close(fdd);
    }
}

char *herpath(ev_list **env,char *key,char *file_name)
{
    ev_list *tmp;

    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key,key) == 0)
            {
               
                char *current = ft_join2(tmp->value,"/");
                char *p = ft_join2(current,file_name);
                return (p);
            }
            tmp = tmp->next;
    }
    free(tmp);
    return NULL;
}
void    herdoc(t_cmd *cmd,ev_list **env)
{
    (void)env;
   
    if (cmd->redirection == 4)
    {
        char *file_name = "outfile.txt";
        char *typ;
        int rd;
        char *p = herpath(env,"PWD",file_name);
        cmd->herd = open(file_name,O_CREAT | O_RDWR , 0644);
        size_t size = strlen(cmd->redirection_file);
        typ = malloc(sizeof(char *)* size);
        typ[size] = '\0';
        while (1)
        {
            if ((rd = read(STDOUT_FILENO,typ,size)) < 1)
            {
                if (!rd)
                {
                    free(p);
                    free(typ);
                    perror("read");
                }
            }
            if (ft_strcmp(typ,cmd->redirection_file) == 0)
            {
                close(cmd->herd);
                cmd->herd = open(file_name,O_RDONLY,0644);
                dup2(cmd->herd,STDIN_FILENO);
                close(cmd->herd);
                unlink(p);
                free(p);
                free(typ);
                return ;
            }
            write(cmd->herd,typ,size);
        }
    }
}


void exec_cmd(t_cmd *cmd,ev_list **env,char **envp)
{
    (void)env;
    (void)envp;
    (void)cmd;
    int cnt_pipe = 0;
    int j = 0;
    int fdd = 0;
    int fd[2];

    if (cmd->next == NULL)
    {
        if (ft_strcmp(cmd->name,"cd") == 0)
        {
            if (check_builting(cmd,env) == 1)
                return ;
        }
    }
    while (cmd != NULL)
    {
        cmd->vex = execve_cmd(cmd,*env);
        char *args1[] = {cmd->name,cmd->args[0], NULL};
        if (pipe(fd) == -1) {
            printf("pipe fails\n");
            return ;
        }
        cmd->pid = fork();
        if (cmd->pid == -1)
        {
            printf("fork fails\n");
            return ;
        }
        if (cmd->pid == 0)
        {
            signal(SIGQUIT,sighandler);
            if (fdd != 0)
            {
                dup2(fdd,STDIN_FILENO);
                close(fdd);
            }
            if (cmd->next != NULL)
            {
                dup2(fd[1],STDOUT_FILENO);
                close(fd[1]);
            }
            redir(cmd);
            herdoc(cmd,env);
            close(fd[0]);
            if (check_builting(cmd,env) != 1)
            {
                execve(cmd->vex,args1,(char **)env);
                free((char *)cmd->vex);
                // exit(1);
            }
            // else
            //     free((char *)cmd->vex);
            // if (cmd->next != NULL)
            //         exit(1);
            // if (cmd->redirection == 4)
            //         exit(1);
            exit(1);
        }
        if (fdd != 0)
            close(fdd);
        fdd = fd[0];
        close(fd[1]);
	    cmd = cmd->next;
        cnt_pipe++;
    }
    while (j < cnt_pipe)
    {
        wait(NULL);
        j++;
    }
}

