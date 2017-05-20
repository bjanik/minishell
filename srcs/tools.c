/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:36:02 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/18 15:26:06 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_prompt(void)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, MAXPATHLEN)))
		ft_printf("%swhere am I?%s %s%C%s ", BOLD_CYAN, RESET, BOLD_GRN, 0x21E8,
				RESET);
	else
		ft_printf("%s%s%s %s%C%s ", BOLD_CYAN, pwd, RESET, BOLD_GRN, 0x21E8,
				RESET);
	ft_strdel(&pwd);
}

int		check_access(char *cmd, char **cmd_arg, char **envir)
{
	struct stat	info;

	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK))
			return (1);
		stat(cmd, &info);
		if (S_ISDIR(info.st_mode))
			return (-1);
		else
			execve(cmd, cmd_arg, envir);
	}
	return (0);
}

int		cmd_is_builtin(char **cmd)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(cmd[0], g_builtins[i].builtin_name))
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_get_cmds(void)
{
	char	*tmp;
	char	*line;
	char	**cmds;
	int		i;

	i = 0;
	if (get_next_line(0, &line) < 1)
		exit(0);
	tmp = line;
	cmds = ft_strsplit(line, ';');
	ft_strdel(&line);
	while (cmds[i])
	{
		tmp = cmds[i];
		cmds[i] = ft_strtrim(tmp);
		ft_strdel(&tmp);
		i++;
	}
	return (cmds);
}

char	**get_cmd_path(t_env *env)
{
	char	**paths;
	t_env	*path;

	paths = NULL;
	if ((path = ft_getenv(env, "PATH")))
		paths = ft_strsplit(path->var_value, ':');
	return (paths);
}
