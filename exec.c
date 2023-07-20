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

char **exec_args(t_cmd *cmd,ev_list **env)
{
    (void)env;
    (void)cmd;
    int i = 0;
    while(cmd != NULL) 
    {
        i = 0;
        if (cmd->args[0] == NULL)
            return (cmd->args);
        else
        {
            while(cmd->args[i] != NULL)
                i++;
            return (cmd->args);
        }
        cmd = cmd->next;
    }
    return (NULL);
}
void exec_cmd(t_cmd *cmd,ev_list **env)
{
    (void)env;
    (void)cmd;
    // execve_cmd(cmd,env);
    t_cmd *tmp = cmd;
    int e_exit = 0;
    int cnt_pipe = 0;
    // int flag = 0;
    int prev_pipe[2] = {0,1};
    while (tmp != NULL)
    {
        tmp = tmp->next;
        cnt_pipe++;
    }
    int i = 0;
    tmp = cmd;
    if (cnt_pipe == 1)
    {
        char *p = execve_cmd(tmp,env);
        // cmd->args = exec_args(tmp,env);
			if (check_builting(tmp, env) == 1)
            {
	            return ;
            }
            else
            {
                tmp->pid = fork();
                if (tmp->pid == -1) 
                {
                    printf("fork fails\n");
                    return ;
                }
                if (tmp->pid == 0)
                {
                    char *args[] = {cmd->name,cmd->args[0], NULL};
                     if ( execve(p,args,NULL) == -1)
                    {
                        printf("execve fails \n");
                        exit(0);
                    }
                }
               
            }
            // exit(0);
    }
    while (i < cnt_pipe)
    {
        if (pipe(tmp->pip) == -1) {
            printf("pipe fails\n");
            return ;
        }
        tmp->pid = fork();
        if (tmp->pid == -1) {
            printf("fork fails\n");
            return ;
        }
        char *p = execve_cmd(tmp,env);
        cmd->args = exec_args(tmp,env);
        if (tmp->pid == 0)
        { 
            
            close(prev_pipe[1]);
            dup2(prev_pipe[0], 0); 
            close(prev_pipe[0]); 

			close(tmp->pip[0]);
			dup2(tmp->pip[1], 1);
			close(tmp->pip[1]);
			if (check_builting(tmp, env) == 1)
            {
                printf("inside");
	            exit(0);
            }
            else
            {
                    char *args1[] = {cmd->name,cmd->args[0], NULL};
                if ( execve(p,args1,NULL) == -1)
                {
                    printf("execve fails \n");
                    exit(0);
                }
               
            }
            exit(0);
		}
		else 
        {
		    prev_pipe[0] = tmp->pip[0];
		    prev_pipe[1]= tmp->pip[1];
		    close(prev_pipe[0]);
		    close(tmp->pip[1]);
		    close(tmp->pip[0]);
            
	    }
	    tmp = tmp->next;
        i++;
    }
    free(tmp);
	close(prev_pipe[1]);
    waitpid(cmd->pid,&e_exit,0);
	wait(NULL);
}
