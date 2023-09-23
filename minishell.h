# ifndef MINISHELL_H
# define MINISHELL_H

#define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
  #include <sys/types.h>
       #include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <ctype.h>

typedef enum e_redirection
{
    REDIR_NONE,
    REDIR_INPUT,
    REDIR_OUTPUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} t_redirection;

typedef struct s_cmd 
{
    int outf;
    int inf;
    const char  *vex;
    char **Expo;
    int  pid;
    int herd;
    int arg_count;
    int pip[2];
    char *name;
    char **args;
    t_redirection redirection;
    char *redirection_file;
    struct s_cmd *next;
} t_cmd;

typedef struct e_list
{
    char *key;
    char *value;
    struct e_list *next;
}   ev_list;
/*lexer*/



/*parse*/
t_cmd* parse_input(char *input);
void print_commands(t_cmd *head);
void handle_pipe(char **token, char **lasts, t_cmd **current);
void handle_redirection(char **token, char **lasts, t_cmd *current);
t_cmd* create_command(char *name);
void add_argument(t_cmd *command, char *arg);

/*func_sup*/
char* custom(char* str, char* delims, char** saveptr);
char* custom_str(char* str, char* delims);

/*exec*/
char	**ft_split( char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void addback(ev_list **list, ev_list *new);
ev_list *key_value(char *key, char *value);
void exec_cmd(t_cmd *cmd,ev_list **env,char **envp);
int check_builting(t_cmd *cmd, ev_list **env);
char *ft__strdup(char *str);
ev_list *key_value(char *key, char *value);
void addback(ev_list **list, ev_list *new);
char    *execve_cmd(t_cmd *cmd, ev_list *env);
// void exec_cmd(t_cmd *cmd,ev_list **env,char **envp);
// char **get_path(ev_list *env);
int checkbuilt(t_cmd *cmd, ev_list **env);
char **get_path(ev_list *env,t_cmd *cmd);
void    free4free(char **tmp);
void ft_echo(t_cmd *cmd, ev_list *env);
void    ft_unset(ev_list **env, t_cmd *cmd);
void    ft_cd(t_cmd *cmd, ev_list **env);
void ft_env(ev_list *env, t_cmd *cmd);
int ft_len(char *str);
void ft_pwd(ev_list *env);
// void ft_exit(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
// void ft__exit(t_cmd *cmd);
int    checkErrer(t_cmd *cmd,ev_list *env);
char **get_path(ev_list *env,t_cmd *cmd);
int ft_strcmp(char *s1, char *s2);
char *access_ve(char **path,t_cmd *cmd);
char	*ft_join2(char *s1, char *s2);
void    sighandler(int sig);
char **ParsExport(char *input);

/*expand*/
char* replace_env_vars(const char* input);
int check_quotes(const char* input);
char* read_input_with_quotes();
#endif