#include "../minishell.h"

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
    int fd = 0;
    if (cmd) 
    {
        if (!cmd->redirections) 
            return;
    }
    if (ft_strcmp(cmd->name,"cat") == 0)
        fd = 1;
    if (cmd->redirections->redirection_type == REDIR_HEREDOC)
    {
        // signal(SIGINT,sighandler);
        // signal(SIGQUIT,heredoc_signal);
		char *temp = get_next_line(fd);
		if (!temp)
			return ;
		char *line = ft_substr(temp, 0, strlen(temp) - 1);
		free(temp);
        int open_file = open(file_name,O_CREAT | O_RDWR | O_TRUNC,0644);
		while (ft_strcmp(line, cmd->redirections->filename))
		{
			write(open_file, line, strlen(line));
			write(open_file, "\n", 1);
			temp = get_next_line(fd);
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