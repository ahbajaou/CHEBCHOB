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

void    herdoc(t_cmd *cmd)
{


    char *file_name = "outfile.txt";
    if (cmd->redirection == 4)
    {
        char *typ;
        int rd;
        cmd->herd = open(file_name,O_CREAT | O_RDWR , 0644);
        size_t size = strlen(cmd->redirection_file);
        typ = malloc(sizeof(char *)* size);
        typ[size] = '\0';
        while (1)
        {
            if ((rd = read(STDOUT_FILENO,typ,size)) < 1)
            {
                if (!rd)
                    perror("read");
            }
            if (ft_strcmp(typ,cmd->redirection_file) == 0)
            {
                close(cmd->herd);
                cmd->herd = open(file_name,O_RDONLY,0644);
                dup2(cmd->herd,STDIN_FILENO);
                close(cmd->herd);
                unlink("/home/ahmed/Desktop/githup/CHEBCHOB/outfile.txt");
                break ;
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

    while (cmd != NULL)
    {
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
            close(fd[0]);
            redir(cmd);
            herdoc(cmd);
            if (check_builting(cmd,env) != 1)
            {
                execve(execve_cmd(cmd,*env),args1,envp);
                perror("execve");
                exit(1);
            }
            if (cmd->next != NULL)
                exit(1);
            if (cmd->redirection == 3)
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

