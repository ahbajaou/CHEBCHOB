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

// void exec_cmd(t_cmd *cmd,ev_list **env)
// {
    // (void)env;
    // (void)cmd;
    // int i = 0;
    // while(cmd != NULL) 
    // {
    //     printf("Command: %s\n", cmd->name);
    //     i = 0;
    //     if (cmd->args[0] == NULL)
    //         printf("La commande n'a pas d'arguments.\n");
    //     else 
    //     {
    //         printf("La commande a des arguments:\n");
    //         while(cmd->args[i] != NULL)
    //         {
    //             printf("%s\n", cmd->args[i]);
    //             i++;
    //         }
    //     }
    //     cmd = cmd->next;
    // }
void exec_cmd(t_cmd *cmd,ev_list **env)
{
    (void)env;
    (void)cmd;
    execve_cmd(cmd,env);
    t_cmd *tmp = cmd;
    int e_exit = 0;
    int flag = 0;
    int prev_pipe[2] = {0,1};

    while (tmp != NULL)
    {
            printf("000here00\n");
        if (tmp->next->name == NULL)
        {
            flag = -1;
        }
        if (pipe(tmp->pip) == -1) {
            printf("pipe fails\n");
            return ;
        }
        tmp->pid = fork();
        if (tmp->pid == -1) {
            printf("fork fails\n");
            return ;
        }
        if (tmp->pid == 0)
        { 
            if (flag == -1)
                printf("loops\n");
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
                char *p = execve_cmd(tmp,env);
                char *args[3];
                printf("--%s---\n",cmd->args[0]);
                if (cmd->args[0] == NULL)
                {
                    args[0] = p;
                    args[1] = "-l";
                    args[2] = NULL;
                    printf("NULL\n");

                }
                else
                    {
                        args[0] = p;
                        args[2] = NULL;

                    }
                printf("here\n");
                printf("--%s---",cmd->args[0]);
                execve(p,args,NULL);
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
    }
    free(tmp);
	close(prev_pipe[1]);
    waitpid(cmd->pid,&e_exit,0);
	wait(NULL);
}
