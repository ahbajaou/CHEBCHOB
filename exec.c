/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:46:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/16 11:25:18 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void    exec_cmd(t_cmd *cmd,ev_list **env)
{
    (void)cmd;
    (void)env;
    t_cmd *tmp;

    tmp = cmd;
    // printf("--%s---\n",tmp->name);

    // int i = 0;
    int e_exit = 0;
    // cmd->outf = 0;
    // cmd->inf = 0;
    int *prev_pipe = NULL;
    while (tmp)
    {
        if (pipe(cmd->pip) == -1)
            printf("pipe fails\n");
        cmd->pid = fork();
        if (cmd->pid == -1)
        {
            printf("fork fails\n");
            return ;
        }
        if (cmd->pid == 0)
        { 
            close(cmd->pip[0]);
            dup2(cmd->pip[1],1);
            close(cmd->pip[1]);
            if (check_builting(cmd,env) != 0)
                printf("--start exec--\n");
            printf("child already\n");
            // exit(0);
        }
        else
        {
            close(cmd->pip[1]);
            dup2(cmd->pip[0],0);
            close(cmd->pip[0]);
            prev_pipe = tmp->pip;
        }
        // close(cmd->pip[1]);
        tmp = tmp->next;
        waitpid(cmd->pid,&e_exit,0);
        // wait(NULL);
        // cmd->arg_count++;
    }
    close(cmd->pip[1]);
    close(cmd->pip[0]);
    free(tmp);
}

// void exec_cmd(t_cmd *cmd,ev_list **env)
// {
//     t_cmd *tmp = cmd;
//     int e_exit = 0;
//     int prev_pipe[2] = {0,1};

//     while (tmp != NULL)
//     {
//         if (pipe(tmp->pip) == -1) {
//             printf("pipe fails\n");
//             return ;
//         }

//         tmp->pid = fork();

//         if (tmp->pid == -1) {
//             printf("fork fails\n");
//             return ;
//         }
//         if (tmp->pid == 0)
//         { 
//             close(prev_pipe[1]); 
//             dup2(prev_pipe[0], STDIN_FILENO); 
//             close(prev_pipe[0]); 

// 			close(tmp->pip[0]);
// 			dup2(tmp->pip[1], STDOUT_FILENO);
// 			close(tmp->pip[1]);
// 			if (check_builting(tmp, env) != 0)
// 				printf("--start exec--\n");

//             printf("start pipe\n");

// 			printf("child already\n");
// 	        exit(0);
// 		}
// 		else 
//         {
// 		    close(prev_pipe[0]);
		
// 		    prev_pipe[0] = tmp -> pip[0];
// 		    prev_pipe [1]= tmp -> pip[1];

// 		    close(tmp->pip[1]) ;
// 	    }
	    
// 	    tmp = tmp->next;
//     }

// 	close(prev_pipe[0]);
//     waitpid(cmd->pid,&e_exit,0);
// 	wait(NULL);
//     free(tmp);
// }