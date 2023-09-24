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

extern struct global_status g_exit;

char *herpath(ev_list **env,char *key,char *file_name)
{
    ev_list *tmp;

    tmp = *env;
    char *p;
    char *current;
    while (tmp)
    {
        if (ft_strcmp(tmp->key,key) == 0)
            {
               
                current = ft_join2(tmp->value,"/");
                p = ft_join2(current,file_name);
                return (p);
            }
            tmp = tmp->next;
    }
    free(tmp);
    return NULL;
}

void redir(t_cmd *cmd)
{
    int fdd;
    if (cmd->redirection == 1)
    {
        cmd->inf = open(cmd->redirection_file,O_RDONLY , 0644);
        dup2(cmd->inf,STDIN_FILENO);
        close(cmd->inf);
    }
    if (cmd->redirection == 2)
    {
        cmd->outf = open(cmd->redirection_file, O_CREAT | O_RDWR ,0644);
        dup2(cmd->outf,STDOUT_FILENO);
        close(cmd->outf);
    }
    if (cmd->redirection == 3)
    {
        fdd = open(cmd->redirection_file, O_CREAT | O_RDWR | O_APPEND , 0644);
        dup2(fdd,STDOUT_FILENO);
        close(fdd);
    }
}

void    herdoc(t_cmd *cmd,ev_list **env)
{
    (void)env;
    char *file_name = "tmp/outfile.txt";
    if(cmd->redirection == 4)
    {
		//heredoc_signal();
        // signal(SIGINT,sighandler);
        signal(SIGQUIT,sighandler);
		char *temp = get_next_line(0);
		if (!temp)
			exit(0);
		char *line = ft_substr(temp, 0, strlen(temp) - 1);
		free(temp);
        int open_file = open(file_name,O_CREAT | O_RDWR | O_TRUNC,0644);
		while (ft_strcmp(line, cmd->redirection_file))
		{
			write(open_file, line, strlen(line));
			write(open_file, "\n", 1);
			temp = get_next_line(0);
            free(line);
            if (!temp)
                return ;
			line = ft_substr(temp, 0, strlen(temp) - 1);
			free(temp);
		}
		close(open_file);
        open_file = open(file_name,O_RDONLY,0644);
        dup2(open_file,STDIN_FILENO);
        close(open_file);
        unlink(file_name);
        free(line);
    }
}

    global_status g_exit;
void exec_cmd(t_cmd *cmd,ev_list **env,char **envp)
{
    (void)env;
    (void)envp;
    (void)cmd;
    int cnt_pipe = 0;
    int j = 0;
    int fdd = 0;
    // int flag = 0;
    int fd[2];
    // g_exit._exit = 0;
    while (cmd != NULL)
    {
        
        cmd->vex = execve_cmd(cmd,*env);
        if (checkErrer(cmd,*env) == 0)
        {
            if (cmd->vex)
                free(cmd->vex);
            if (checkbuilt(cmd,env) == 1)
                return ;
            return ;
        }
        char *args1[] = {cmd->name,cmd->args[0], NULL};
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return ;
        }
        cmd->pid = fork();
        if (cmd->pid == -1)
        {
            perror("fork");
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
            herdoc(cmd,env);
            close(fd[0]);
            redir(cmd);
            if (check_builting(cmd,env) != 1)
            {
                if (!cmd->vex)
                    return ;
                if (!execve(cmd->vex,args1,envp))
                    perror("execve");
            }
            exit(1);
        }
        free((char *)cmd->vex);
        if (fdd != 0)
            close(fdd);
        fdd = fd[0];
        close(fd[1]);
	    cmd = cmd->next;
        cnt_pipe++;
    }
    // waitpid(cmd->pid,&g_exit._exit,0);
    while (j < cnt_pipe)
    {
        wait(NULL);
        j++;
    }
}
