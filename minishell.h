/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:19:15 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/30 03:09:56 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum errortype
{
	ERROR_DOC,
	ERROR_SYNTAX,
	ERROR_PIPE,
	ERROR_DOUBLE_PIPE,
	REDIR_ERROR,
	REDIR_ERROR_L1R1,
	ERROR_CNF,
}							t_errortype;

typedef enum e_redirection
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redirection;

typedef struct s_cmd
{
	char					*res;
	size_t					i_resu;
	char					q_c;
	int						is_escaped;
	size_t					required_length;
	int						i;
	size_t					j;
	int						outf;
	int						inf;
	int						cnt_pipe;
	char					*vex;
	char					**expo;
	char					*execve[3];
	int						pid;
	int						herd;
	int						arg_count;
	int						pip[2];
	char					*name;
	struct s_redirection	*redirections;
	char					**args;
	t_redirection			redirection;
	char					*redirection_file;
	struct s_cmd			*next;
	char					*old_str;
	char					*continuation;
	size_t					old_str_len;
	size_t					continuation_len;
	char					*str;
	char					*replaced_str;
	int						flag;
	char					*processed_str;
}							t_cmd;

typedef struct s_redirection
{
	char					*filename;
	t_redirection			redirection_type;
	struct s_redirection	*next;
}							t_redirection_list;

typedef struct e_list
{
	char					*key;
	char					*value;
	int 					flag;
	char 					*str;
	char					*replaced_str;
	char					*processed_str;
	struct e_list			*next;
}							t_list;

typedef struct t_global_status
{
	int						_exit;

}							t_global_status;

/*lexer*/
size_t						calculate_required_length(const char *input);
char						*replace_env_vars(char *input);
char						*read_input_with_quotes(void);
/*parse*/
t_cmd						*parse_input(char *input);
void						print_commands(t_cmd *head);
void						handle_pipe(char **token, char **lasts,
								t_cmd **current);
void						handle_redirection(char **token, char **lasts,
								t_cmd *current);
t_cmd						*create_command(char *name);
void						add_argument(t_cmd *command, char *arg);
void						add_redirection(t_cmd *command, char *filename,
								t_redirection redirection);
/*libft*/
char						*my_strcat(char *dest, const char *src);
char						*my_strdup(const char *s);
size_t						my_strspn(const char *s, const char *accept);
int							my_strcmp(const char *s1, const char *s2);
void						*my_calloc(size_t nmemb, size_t size);
void						*my_realloc(void *ptr, size_t old_size,
								size_t new_size);
size_t						my_strlen(const char *str);
int							my_isalnum(int c);
void						ft_strchr(char *str, char c);
/*libft*/
size_t						ft_get_env_replace(char *input, t_cmd *ubuntu,
								size_t required_length, size_t i_res);
char						ft_pedro(char quote_char);
char						*replace_env_vars(char *input);
size_t						ft_get_env_replace(char *input, t_cmd *ubuntu,
								size_t required_length, size_t i_res);
void						update_quote_state(char current, char *quote_char,
								int is_escaped);
int							check_quotes(const char *input);
// size_t  calculate_required_length(const char *input);
// static size_t    get_var_length(const char **input);
/*func_sup*/
char						*custom(char *str, char *delims, char **saveptr);
char						*custom_str(char *str, char *delims);
/*exec*/
char						**ft_split(char *s, char c);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
void						addback(t_list **list, t_list *new);
t_list						*key_value(char *key, char *value);
void						exec_cmd(t_cmd *cmd, t_list **env, char **envp,
								int cnt_pipe);
int							check_builting(t_cmd *cmd, t_list **env);
char						*ft__strdup(char *str);
t_list						*key_value(char *key, char *value);
void						addback(t_list **list, t_list *new);
char						*execve_cmd(t_cmd *cmd, t_list *env);
// void exec_cmd(t_cmd *cmd,t_list**env,char **envp);
// char **get_path(t_list*env);
int							checkbuilt(t_cmd *cmd, t_list **env);
void						parentbuilt(t_cmd *cmd, t_list **env);
char						**get_path(t_list *env, t_cmd *cmd);
void						free4free(char **tmp);
void						ft_echo(t_cmd *cmd);
void						ft_unset(t_list **env, t_cmd *cmd);
void						ft_cd(t_cmd *cmd, t_list **env);
void						ft_env(t_list *env, t_cmd *cmd);
int							ft_len(char *str);
void						ft_pwd(t_list *env);
void						redir(t_cmd *cmd);
void						herdoc(t_cmd *cmd);
// void ft_exit(t_cmd *cmd);
void						ft_exit(t_cmd *cmd);
// void ft__exit(t_cmd *cmd);
int							checkerrer(t_cmd *cmd, t_list *env);
char						**get_path(t_list *env, t_cmd *cmd);
int							ft_strcmp(char *s1, char *s2);
char						*access_ve(char **path, t_cmd *cmd);
char						*ft_join2(char *s1, char *s2);
char						*ft_join3(char *s1, char *s2);
void						sighandler(int sig);
char						**parsexport(char *input);
char						*get_next_line(int fd);
int							checkbuilt2(t_cmd *cmd, t_list **env);
char						*skipeq(char *str, char sep);
int							ft_cherchr(char *str, char c);
int							_exit_status(char *input);
int							checkdollar(char *str);
void						exec_cmd2(t_cmd *cmd, t_list **env);
void						pipeline(t_cmd *cmd, int fdd, int fd[2]);
void						_redirection(t_cmd *cmd);
void						executecmd(t_cmd *cmd, t_list **env, char **envp);
void						_waitpid(int cnt_pipe);
int							errexit(t_cmd *cmd);
void						delet_unset(t_list **env, char *key);
char						*skipeq(char *str, char sep);
int							check_double(t_list **env, char *key, char *value);
int							checkjoin(char *key);
void						print_env(t_list **env, int flag);
int							checkexpo(char *key, char *value, t_list **env);
char						**splitexpo(const char *s, char c);
void						freesplitexpo(char **str);
int							cnt_len(char *s, char c);
int							count_strings2(const char *s, char c);
char						*allocation_string2(const char *s, char c);
char						**ft_free2(char **str, size_t i);
t_list						*_env(char **envp);
int							ft_cherchr(char *str, char c);
void						sighandler(int sig);
void						sigcmd(void);
void						sigchild(void);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
/*expand*/
// int							check_quotes(const char *input);
char						*read_input_with_quotes(void);
char						*remove_double_quotes(const char *str);
/*free*/
void						free_command(t_cmd *command);
/*error*/
void						error(t_errortype, t_cmd *cmd);
// void						execute_command(t_cmd *cmd, char **envp, t_list *env);
int							outdor_pars(char *str);
char						*strred(char *str);
void						free_cmd3(t_cmd *commands);
void						free_cmd2(t_cmd *commands);
char						*space_in(char *replaced_str, char *str);
char						*concatenate_with_newline(char *old_str,
								char *continuation);
void						error(t_errortype type, t_cmd *cmd);
void						handle_back_slash(t_cmd *b, char *ip);
void						handle_double_quote(t_cmd *b);
void						handle_single_quote(t_cmd *b);
void						handle_dollar_sign(t_cmd *b, char *ip);
void						handle_other_cases(t_cmd *b, char *ip);
char						*replace_env_vars(char *ip);
char						ft_slash_impact(int is_escaped, char quote_char);
char						ft_pedro(char quote_char);
#endif
