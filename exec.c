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

void exec_cmd(t_cmd *cmd,ev_list **env,char **envp)
{
    (void)env;
    (void)envp;
    (void)cmd;
    t_cmd *tmp = cmd;
    // int e_exit = 0;
    int cnt_pipe = 0;
    int fd[2];
    // int flag = 0;
    // int prev_pipe[2] = {0,1};
    int fdd = 0;
    tmp = cmd;
    char *p;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        cnt_pipe++;
    }
    int i = 0;
    while (i < cnt_pipe)
    {
        p = execve_cmd(cmd,*env);
        char *args1[] = {cmd->name,cmd->args[0], NULL};
        if (pipe(fd) == -1) {
            printf("pipe fails\n");
            return ;
        }
        cmd->pid = fork();
        if (cmd->pid == -1) {
            printf("fork fails\n");
            return ;
        }
        if (cmd->pid == 0)
        {  
            dup2(fdd,STDIN_FILENO);
            if (i + 1 != cnt_pipe)
                dup2(fd[1],STDOUT_FILENO);
            close(fd[0]);
			// if (access(p,F_OK))
            // {
            //     printf("insede buitin\n");
            // }
            // check_builting(cmd, env);  
            if (check_builting(cmd,env) != 1)
                execve(p,args1,envp);
            exit(0);
		}
            wait(NULL);
            close(fd[1]);
            fdd = fd[0];
	    cmd = cmd->next;
        i++;
    }
	wait(NULL);
}
