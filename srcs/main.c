/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:42:02 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/09 14:17:50 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cmd_path(t_env *env)
{
	char	**paths;
	t_env	*path;

	paths = NULL;
	if ((path = ft_getenv(env, "PATH")))
		paths = ft_strsplit(path->var_value, ':');
	return (paths);
}

static int	execute_cmd(char **paths, char **cmd, char **envir)
{
	int			i;
	char		*full_cmd_path;
	int			no_perm;

	i = 0;
	no_perm = 0;
	full_cmd_path = NULL;
	if ((no_perm = check_access(cmd[0], cmd, envir)) == -1)
		return (0);
	while (paths && paths[i] && !no_perm)
	{
		full_cmd_path = ft_strnjoin(paths[i], 2, "/", cmd[0]);
		no_perm = check_access(full_cmd_path, cmd, envir);
		ft_strdel(&full_cmd_path);
		i++;
	}
	return (no_perm) ? PERMISSION_DENIED : COMMAND_NOT_FOUND;
}

static void	fork_and_execute(t_shell *shell)
{
	int	ret;

	ret = 0;
	if ((shell->ret = fork()) < 0)
		ft_perror("Can't fork");
	if (!shell->ret)
	{
		shell->paths = get_cmd_path(shell->env);
		shell->envir = env_to_tab(shell->env);
		ret = execute_cmd(shell->paths, shell->cmd, shell->envir);
		if (ret == COMMAND_NOT_FOUND)
			ft_error_msg("bsh :command not found: ", shell->cmd[0]);
		else if (ret == PERMISSION_DENIED)
			ft_error_msg("bsh :permission denied: ", shell->cmd[0]);
		else
			ft_printf("bsh : %s: is a directory\n", shell->cmd[0]);
		exit(ret);
	}
	else
	{
		waitpid(shell->ret, &shell->status, WUNTRACED);
		ft_free_string_tab(&shell->paths);
	}
}

static int	minishell_loop(t_shell *shell)
{
	int	i;

	i = 0;
	while (42)
	{
		minishell_prompt();
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

int			main(int argc, char **argv, char **environ)
{
	t_shell	*shell;
	int		minishell_ret;

	(void)argv;
	shell = NULL;
	if (argc != 1)
		minishell_ret = COMMAND_NOT_FOUND;
	else
	{
		shell = init_minishell(environ);
		minishell_ret = minishell_loop(shell);
	}
	return (minishell_ret);
}
