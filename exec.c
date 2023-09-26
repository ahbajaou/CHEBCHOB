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

void redir(t_cmd *cmd)
{
     if (!cmd || !cmd->redirections)
        return;
    int fdd;
    if (cmd->redirections->redirection_type == REDIR_INPUT)
    {
        cmd->inf = open(cmd->redirections->filename,O_RDONLY , 0644);
        dup2(cmd->inf,STDIN_FILENO);
        close(cmd->inf);
    }
    if (cmd->redirections->redirection_type == REDIR_OUTPUT)
    {
        cmd->outf = open(cmd->redirections->filename, O_CREAT | O_RDWR ,0644);
        dup2(cmd->outf,STDOUT_FILENO);
        close(cmd->outf);
    }
    if (cmd->redirections->redirection_type == REDIR_APPEND)
    {
        fdd = open(cmd->redirections->filename, O_CREAT | O_RDWR | O_APPEND , 0644);
        dup2(fdd,STDOUT_FILENO);
        close(fdd);
    }
}

// void    heredoc_signal(int sig)
// {
//     if (sig == SIGQUIT)
//         {
//             g_exit._exit = 0;
//             exit(0);
//         }
// }
void    herdoc(t_cmd *cmd,ev_list **env)
{
    (void)env;
    char *file_name = "outfile";
    if (cmd) 
    {
        if (!cmd->redirections) 
            return;
    }
    if (cmd->redirections->redirection_type == REDIR_HEREDOC)
    {
        // signal(SIGINT,sighandler);
        // signal(SIGQUIT,heredoc_signal);
		char *temp = get_next_line(0);
		if (!temp)
			exit(0);
		char *line = ft_substr(temp, 0, strlen(temp) - 1);
		free(temp);
        int open_file = open(file_name,O_CREAT | O_RDWR | O_TRUNC,0644);
		while (ft_strcmp(line, cmd->redirections->filename))
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
        if (cmd->redirections->next)
            return ;
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
    int fd[2];
    while (cmd != NULL)
    {
        cmd->vex = execve_cmd(cmd,*env);
        if (!cmd->vex)
            cmd->vex = ft__strdup(cmd->name);
        char *args1[] = {cmd->name,cmd->args[0], NULL};
        if (checkErrer(cmd,*env) == 0)
        {
            if (cmd->vex)
                free(cmd->vex);
            if (checkbuilt(cmd,env) == 1)
                return ;
            return ;
        }
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
            close(fd[0]);
            while (cmd->redirections)
            {
                redir(cmd);
                herdoc(cmd,env);
                cmd->redirections = cmd->redirections->next;
            }
            if (check_builting(cmd,env) != 1)
            {
                if (!cmd->vex)
                    return ;
                if (!execve(cmd->vex,args1,envp))
                    perror("execve");
            }
            exit(1);

        }
        if(cmd->vex)
            free((char *)cmd->vex);
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
