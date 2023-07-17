/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:36:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/17 04:51:11 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    execve_cmd(t_cmd *cmd, ev_list **env)
{
    (void)cmd;
    (void)env;
    
    char **path = get_path(env);
    // char *args[3];

    char *p = access_ve(path,cmd);
    // if (!cmd->args[0][0])
    //     printf("NULL\n");
    // int i = 0;
    // while (args[i])
    // {
    //     printf("--[%s]---\n",args[i]);
    //     i++;

    // }
    // exit(0);
        if (!access(p,F_OK))
        {
            printf("--%s---\n",p);
            execve(p,cmd->args,NULL);
        }

    exit(0);
    // int i = 0;
    // int j = 0;
    // char *current;
    // int pid;
    // int ex;

    // i = 0;
    // j = 0;
    // char *p;
    // pid = fork();
    //  char* const envp[] = {"TERM=xterm", NULL};
    // if (pid == 0)
    // {
    //     while (cmd->args[i])
    //     {
    //         j = 0;
    //         while (spl[j])
    //         {
    //             current = ft_join2(spl[j],"/");
    //             p = ft_join2(current,cmd->args[i]);
    //             if (!access(p,F_OK))
    //             {
    //                 if (execve(p,&cmd->name,envp))
    //                     exit(0);
    //             }

    //             j++;
    //         }

    //         i++;
    //     }
    // }
    // else
    //     waitpid(pid,&ex,0);
    return (0);
}
