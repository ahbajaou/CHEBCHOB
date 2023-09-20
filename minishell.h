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
    int  pid;
    int herd;
    char *vex;
    int arg_count;
    int pip[2];
    char *name;
    char **args;
    t_redirection redirection;
    char *redirection_file;
    int dup_number;           
    char *redirection_cmd;    
    char **redirection_args; 
    int redirection_arg_count;
    struct s_cmd *next;
} t_cmd;

typedef struct e_list
{
    char *key;
    char *value;
    struct e_list *next;
}   ev_list;
/*lexer*/
char** lexer(char* input);
void free_tokens(char** tokens);
/*parse*/
// t_cmd* parse_input(char *input);
t_cmd* parse_input_from_tokens(char** tokens);
void print_commands(t_cmd *head);
void handle_pipe(char **token, char **lasts, t_cmd **current);
char* handle_redirection(char **tokens, t_cmd *current, int *i, int tokens_length);
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
char **get_path(ev_list *env,t_cmd *cmd);
void ft_echo(t_cmd *cmd, ev_list *env);
void    ft_unset(ev_list **env, t_cmd *cmd);
void    ft_cd(t_cmd *cmd, ev_list **env);
void ft_env(ev_list *env, t_cmd *cmd);
int ft_len(char *str);
// void ft_pwd(void);
void ft_pwd(ev_list *env);
// void ft_exit(t_cmd *cmd);
 void ft_exit(t_cmd *cmd);
int ft_strcmp(char *s1, char *s2);
char *access_ve(char **path,t_cmd *cmd);
char	*ft_join2(char *s1, char *s2);

/*expand*/
char* replace_env_vars(const char* input);
int check_quotes(const char* input);
char* read_input_with_quotes();

/*free*/
void free_command(t_cmd *command);


void print_args(char** args);
void print_command_details(t_cmd *command);
void print_all_commands(t_cmd *head);
#endif