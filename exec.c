/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:46:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/17 03:04:02 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void exec_cmd(t_cmd *cmd,ev_list **env)
{
    (void)env;
    (void)cmd;
    execve_cmd(cmd,env);
    // t_cmd *tmp = cmd;
    // int e_exit = 0;
    // int prev_pipe[2] = {0,1};

    // while (tmp->next != NULL)
    // {
    //     if (pipe(tmp->pip) == -1) {
    //         printf("pipe fails\n");
    //         return ;
    //     }
    //     tmp->pid = fork();
    //     if (tmp->pid == -1) {
    //         printf("fork fails\n");
    //         return ;
    //     }
    //     if (tmp->pid == 0)
    //     { 
    //         close(prev_pipe[1]);
    //         dup2(prev_pipe[0], 0); 
    //         close(prev_pipe[0]); 

	// 		close(tmp->pip[0]);
	// 		dup2(tmp->pip[1], 1);
	// 		close(tmp->pip[1]);
	// 		if (check_builting(tmp, env) == 0)
	//             exit(0);
	// 	}
	// 	else 
    //     {
	// 	    prev_pipe[0] = tmp->pip[0];
	// 	    prev_pipe[1]= tmp->pip[1];
	// 	    close(prev_pipe[0]);
	// 	    close(tmp->pip[1]);
	// 	    close(tmp->pip[0]);
            
	//     }
	//     tmp = tmp->next;
    // }
    // // exit(0);
    // if (check_builting(tmp, env) != 0)
    // {
    //     printf("not here\n");
    //         return ;
    // }
    // if (execve_cmd(tmp,env) != 0)
    // {

    //     printf("--%s---\n",tmp->name);
    //         return ;
    // }
    // free(tmp);
	// close(prev_pipe[1]);
    // waitpid(cmd->pid,&e_exit,0);
	// wait(NULL);
}