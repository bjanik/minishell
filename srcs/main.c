/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:42:02 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/26 17:51:41 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_perror(char *error)
{
	perror(error);
	exit(-1);
}

int			cmd_is_builtin(char **cmd_arg)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(cmd_arg[0], g_builtins[i].builtin_name))
			return (i);
		i++;
	}
	return (-1);
}

static char	**get_cmd_path(t_env *env)
{
	char	**paths;
	t_env	*path;

	paths = NULL;
	if ((path = ft_getenv(env, "PATH")))
		paths = ft_strsplit(path->var_value , ':');
	return (paths);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;
	t_env	*ptr;
	int		i;

	i = 0;
	tab = NULL;
	ptr = env;
	if (!(tab = (char**)malloc((size_env(env) + 1) * sizeof(char*))))
		ft_perror("malloc");
	while (env)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(env->var_value) +
							ft_strlen(env->var_name) + 2))))
			ft_perror("malloc");
		ft_strcpy(tab[i], env->var_name);
		ft_strcat(tab[i], "=");
		ft_strcat(tab[i++], env->var_value);
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int			execute_cmd(char **paths, char **cmd_arg, char **envir)
{
	int		i;
	char	*full_cmd_path;

	i = 0;
	full_cmd_path = NULL;
	while (paths[i])
	{
		if (cmd_arg[0][0] != '/')
			full_cmd_path = ft_strnjoin(paths[i], 2, "/", cmd_arg[0]);
		else
			full_cmd_path = cmd_arg[0];
		ft_printf("%s\n", cmd_arg[0]);
		if (execve(full_cmd_path, cmd_arg, envir) != -1)
		{
			ft_strdel(&full_cmd_path);
			return (1);
		}
		ft_strdel(&full_cmd_path);
		i++;
	}
	return (0);
}

char	**ft_get_cmd(void)
{
	char	*tmp;
	char	*line;
	char	**cmd;

	get_next_line(0, &line);
	tmp = line;
	line = ft_strtrim(tmp);
	free(tmp);
	cmd = ft_strtok(line, "\t ");
	free(line);
	return (cmd);
}

void	fork_and_execute(t_shell *shell)
{
	if ((shell->ret = fork()) < 0)
		ft_perror("fork");
	if (!shell->ret)
	{
		shell->paths = get_cmd_path(shell->env);
		if (!shell->paths && shell->cmd[0][0] != '/')
			ft_printf("bsh :command not found: %s\n", shell->cmd[0]);
		shell->envir = env_to_tab(shell->env);
		if (shell->cmd && execute_cmd(shell->paths, shell->cmd, shell->envir) < 1)
			ft_printf("bsh :command not found: %s\n", shell->cmd[0]);
		exit(COMMAND_NOT_FOUND);
	}
	else
		waitpid(shell->ret, &shell->status, WUNTRACED);

}

int	minishell_loop(t_shell *shell)
{
	int	i;

	i = 0;
	while (42)
	{
		ft_putstr("$> ");
		shell->cmd = ft_get_cmd();
		if (shell->cmd[0] && ((i = cmd_is_builtin(shell->cmd)) != -1)
				&& ft_strcmp(shell->cmd[0], "exit"))
		shell->status = g_builtins[i].builtins(&shell->env, shell->cmd);
		else if (shell->cmd[0] && ft_strcmp(shell->cmd[0], "exit"))
			fork_and_execute(shell);
		else if (shell->cmd[0] && !ft_strcmp(shell->cmd[0], "exit"))
		{
			if (shell->cmd[1] && shell->cmd[2])
				ft_putendl_fd("exit: too many arguments", 2);
			else
				return (ft_exit(shell->env, shell->cmd));
		}
		ft_free_string_tab(&shell->cmd);
	}
	return (0);
}
int			main(int argc, char **argv)
{
	t_shell	b_shell;
	t_shell	*shell;
	int		minishell_ret;

	(void)argv;
	if (argc != 1)
		minishell_ret = COMMAND_NOT_FOUND;
	else
	{
		shell = &b_shell;
		init_minishell(shell);
		minishell_ret = minishell_loop(shell);
	}
	return (minishell_ret);
}
