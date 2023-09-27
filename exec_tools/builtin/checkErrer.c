#include "../../minishell.h"

extern struct global_status	g_exit;

int	Errexit(t_cmd *cmd)
{
	int	i;
	int	j;
	int	m;

	i = 0;
	j = 0;
	m = 0;
	while (cmd->args[i])
	{
		if (((cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z') && i == 0) ||
			((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') && i == 0))
		{
			printf("exit: %s: numeric argument required\n", cmd->args[i]);
			exit(0);
			return (1);
		}
		j = 0;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == '-')
			{
				m++;
				break ;
			}
			if (m > 1)
			{
				printf("exit: %s: numeric argument required\n", cmd->args[i]);
				// exit(0);
				return (1);
			}
			j++;
		}
		i++;
	}
	if (i > 1)
	{
		g_exit._exit = 1;
		printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

void	Errcd(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (chdir(cmd->args[0]))
	{
		g_exit._exit = 127;
		printf("%s No such file or directory\n", cmd->args[0]);
	}
}

void	GetPath(t_cmd *cmd, ev_list *env, int i)
{
	ev_list	*tmp;
	int		p;
	char	**spl;

	p = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			spl = ft_split(tmp->value, '/');
		tmp = tmp->next;
	}
	while (spl[p])
		p++;
	if (ft_strcmp(cmd->name, "./Makefile") == 0)
	{
		g_exit._exit = 126;
		printf("permission denied\n");
	}
	else if (ft_strcmp(spl[p - 1], cmd->name + i) != 0)
		error(ERROR_DOC, cmd);
	else
	{
		g_exit._exit = 126;
		printf("%s : : Is a directory\n", cmd->name + i);
	}
	free4free(spl);
	free(spl);
	free(tmp);
}

void	ErreDoc(t_cmd *cmd, ev_list *env)
{
	int	i;

	(void)cmd;
	(void)env;
	i = 0;
	while (cmd->name[i] == '.' || cmd->name[i] == '/')
		i++;
	GetPath(cmd, env, i);
}

int	checkErrer(t_cmd *cmd, ev_list *env)
{
	if (cmd->name)
	{
		if (ft_strcmp(cmd->name, "exit") == 0)
		{
			if (Errexit(cmd) == 1)
				return (1);
			return (0);
		}
		else if (strstr(cmd->name, "../") || ft_strcmp(cmd->name,
					"./Makefile") == 0)
		{
			ErreDoc(cmd, env);
			return (0);
		}
		else if (ft_strcmp(cmd->name, "export") == 0)
			return (0);
		else if (ft_strcmp(cmd->name, "env") == 0)
			return (0);
		else if (ft_strcmp(cmd->name, "unset") == 0)
			return (0);
	}
	// ErrUnset(cmd,env);
	return (1);
}
