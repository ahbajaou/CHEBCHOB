/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:15:39 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/30 03:09:03 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct t_global_status	g_exit;

// void	init_minishell(t_list *env, char **envp)
// {
// 	env = _env(envp);
// 	signal(SIGINT, sighandler);
// 	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 		exit(0);
// }

// void	read_and_preprocess_line(t_cmd *shell)
// {
// 	char	*tmp;

// 	shell->processed_str = readline("minishell: ");
// 	if (!shell->processed_str)
// 		exit(1);
// 	add_history(shell->processed_str);
// 	shell->processed_str = strred(shell->processed_str);
// 	shell->flag = outdor_pars(shell->processed_str);
// 	tmp = shell->processed_str;
// 	shell->processed_str = remove_double_quotes(shell->processed_str);
// 	free(tmp);
// }

// void	replace_and_treat_line(t_cmd *shell)
// {
// 	char	*tmp;

// 	tmp = shell->processed_str;
// 	shell->processed_str = replace_env_vars(shell->processed_str);
// 	shell->processed_str = space_in(shell->processed_str, tmp);
// 	free(tmp);
// }

// // Exécution de la commande
// void	execute_command(t_cmd *shell, char **envp, t_list *env)
// {
// 	if (!shell->processed_str)
// 		return ;
// 	shell = parse_input(shell->processed_str);
// 	shell->expo = parsexport(shell->processed_str);
// 	if (shell->flag == 0)
// 		exec_cmd(shell, &(env), envp, 0);
// 	free(shell->processed_str);
// 	free_cmd2(shell);
// 	free_cmd3(shell);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell	shell;

// 	(void)ac;
// 	(void)av;
// 	shell.commands = NULL;
// 	init_minishell(&shell, envp);
// 	while (1)
// 	{
// 		read_and_preprocess_line(&shell);
// 		replace_and_treat_line(&shell);
// 		execute_command(&shell, envp,env);
// 	}
// }

void	free_end(char *replaced_str, char *str, t_cmd *commands)
{
	free(replaced_str);
	free(str);
	free_cmd2(commands);
	free_cmd3(commands);
}

void	_signlas(void)
{
	signal(SIGINT, sighandler);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return ;
}

char	*_redline(char *str)
{
	str = readline("minishell: ");
	if (!str)
		exit(1);
	add_history(str);
	str = strred(str);
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*commands;
	t_list	*env;

	(void)ac;
	(void)av;
	env = _env(envp);
	while (1)
	{
		env->flag = 0;
		_signlas();
		env->str = _redline(env->str);
		env->flag = outdor_pars(env->str);
		env->processed_str = remove_double_quotes(env->str);
		free(env->str);
		env->str = env->processed_str;
		env->replaced_str = replace_env_vars(env->str);
		env->replaced_str = space_in(env->replaced_str, env->str);
		if (!env->replaced_str)
			continue ;
		commands = parse_input(env->replaced_str);
		commands->expo = parsexport(env->str);
		if (env->flag == 0)
			exec_cmd(commands, &env, envp, 0);
		free_end(env->replaced_str, env->str, commands);
	}
}
