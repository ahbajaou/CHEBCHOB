# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
  #include <sys/types.h>
       #include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

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

/*func_sup*/
char* custom(char* str, char* delims, char** saveptr);
char* custom_str(char* str, char* delims);

/*exec*/
char	**ft_split( char *s, char c);
void addback(ev_list **list, ev_list *new);
ev_list *key_value(char *key, char *value);
void    exec_cmd(t_cmd *cmd,ev_list **env);
int  check_builting(t_cmd *cmd, ev_list **env);
char *ft__strdup(char *str);
ev_list *key_value(char *key, char *value);
void addback(ev_list **list, ev_list *new);
char    *execve_cmd(t_cmd *cmd, ev_list **env);
char **get_path(ev_list **env);
char *access_ve(char **path,t_cmd *cmd);
char	*ft_join2(char *s1, char *s2);
#endif