/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:19:15 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/27 04:20:18 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_error
{
	ERROR_DOC,
	ERROR_SYNTAX,
	ERROR_PIPE,
	ERROR_DOUBLE_PIPE,
	REDIR_ERROR,
	REDIR_ERROR_L1R1,
	ERROR_CNF,
}							ErrorType;

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
	int						outf;
	int						inf;
	int						j;
	int						cnt_pipe;
	char					*vex;
	char					**Expo;
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
	struct e_list			*next;
}							ev_list;

typedef struct global_status
{
	int						_exit;

}							global_status;

/*lexer*/
void						free_all_cmds(t_cmd *head);
char						*remove_double_quotes(const char *str);
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

/*func_sup*/
char						*custom(char *str, char *delims, char **saveptr);
char						*custom_str(char *str, char *delims);
/*libft-pars*/
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

/*exec*/
char						**ft_split(char *s, char c);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
void						addback(ev_list **list, ev_list *new);
ev_list						*key_value(char *key, char *value);
void						exec_cmd(t_cmd *cmd, ev_list **env, char **envp);
int							check_builting(t_cmd *cmd, ev_list **env);
char						*ft__strdup(char *str);
ev_list						*key_value(char *key, char *value);
void						addback(ev_list **list, ev_list *new);
char						*execve_cmd(t_cmd *cmd, ev_list *env);
/*dollar*/
int							checkdollar(char *str);

int							checkbuilt(t_cmd *cmd, ev_list **env);
void						parentbuilt(t_cmd *cmd, ev_list **env);
char						**get_path(ev_list *env, t_cmd *cmd);
void						free4free(char **tmp);
void						ft_echo(t_cmd *cmd);
void						ft_unset(ev_list **env, t_cmd *cmd);
void						ft_cd(t_cmd *cmd, ev_list **env);
void						ft_env(ev_list *env, t_cmd *cmd);
int							ft_len(char *str);
void						ft_pwd(ev_list *env);
void						redir(t_cmd *cmd);
void						herdoc(t_cmd *cmd, ev_list **env);
// void ft_exit(t_cmd *cmd);
void						ft_exit(t_cmd *cmd);
// void ft__exit(t_cmd *cmd);
int							checkErrer(t_cmd *cmd, ev_list *env);
char						**get_path(ev_list *env, t_cmd *cmd);
int							ft_strcmp(char *s1, char *s2);
char						*access_ve(char **path, t_cmd *cmd);
char						*ft_join2(char *s1, char *s2);
char						*ft_join3(char *s1, char *s2);
void						sighandler(int sig);
char						**ParsExport(char *input);
char						*get_next_line(int fd);
void						freeSplitExpo(char **str);
int							checkbuilt2(t_cmd *cmd, ev_list **env);
char						*skipeq(char *str, char sep);
char						**SplitExpo(const char *s, char c);
int							ft_cherchr(char *str, char c);
int							_exit_status(char *input);

/*expand*/
char						*replace_env_vars(const char *input);
int							check_quotes(const char *input);
char						*read_input_with_quotes(void);

/*free*/
void						free_command(t_cmd *command);

/*error*/
void						error(ErrorType type, t_cmd *cmd);

void						execute_command(char *cmd);
#endif
