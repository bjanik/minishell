/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:42:02 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/19 13:48:03 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

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

static void	fork_and_execute(t_shell *shell, char **cmd)
{
	int	ret;

	ret = 0;
	if ((g_pid = fork()) < 0)
		ft_perror("Can't fork");
	if (!g_pid)
	{
		shell->paths = get_cmd_path(shell->env);
		shell->envir = env_to_tab(shell->env);
		ret = execute_cmd(shell->paths, cmd, shell->envir);
		if (ret == COMMAND_NOT_FOUND)
			ft_error_msg("bsh :command not found: ", cmd[0]);
		else if (ret == PERMISSION_DENIED)
			ft_error_msg("bsh :permission denied: ", cmd[0]);
		else
			ft_printf("bsh : %s: is a directory\n", cmd[0]);
		exit(ret);
	}
	else
	{
		waitpid(g_pid, &shell->status, 0);
		ft_free_string_tab(&shell->paths);
	}
	g_pid = 0;
}

static int	comand(t_shell *shell, char **cmd, int i)
{
	if (cmd && cmd[0] && ((i = cmd_is_builtin(cmd)) != -1)
			&& ft_strcmp(cmd[0], "exit"))
	{
		shell->status = g_builtins[i].builtins(&shell->env, cmd);
		return (0);
	}
	else if (cmd[0] && ft_strcmp(cmd[0], "exit"))
	{
		fork_and_execute(shell, cmd);
		return (0);
	}
	return (1);
}

static int	minishell_loop(t_shell *shell)
{
	int		i;
	int		j;
	char	**cmd;

	while (42)
	{
		minishell_prompt();
		shell->cmds = ft_get_cmds();
		i = 0;
		j = 0;
		while (shell->cmds[i])
		{
			cmd = ft_strtok(shell->cmds[j++], " \t");
			if (comand(shell, cmd, i++) && cmd[0] && !ft_strcmp(cmd[0], "exit"))
			{
				if (cmd[1] && cmd[2])
					ft_putendl_fd("exit: too many arguments", 2);
				else
					return (ft_exit(shell->env, cmd));
			}
			ft_free_string_tab(&cmd);
		}
		ft_free_string_tab(&shell->cmds);
	}
	return (0);
}

int			main(int argc, char **argv, char **environ)
{
	t_shell		*shell;
	int			minishell_ret;

	(void)argv;
	shell = NULL;
	if (argc != 1)
		minishell_ret = COMMAND_NOT_FOUND;
	else
	{
		signal(SIGINT, ft_sighandler);
		signal(SIGTSTP, SIG_IGN);
		shell = init_minishell(environ);
		minishell_ret = minishell_loop(shell);
	}
	return (minishell_ret);
}
