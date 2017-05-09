/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:36:02 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/09 21:08:40 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_prompt(void)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, MAXPATHLEN)))
		ft_perror("getcwd failed");
	ft_printf("%s%s%s %s%C%s ", BOLD_CYAN, pwd, RESET, BOLD_GRN, 0x21E8, RESET);
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

int		cmd_is_builtin(char **cmd_arg)
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

char	**ft_get_cmd(void)
{
	char	*tmp;
	char	*line;
	char	**cmd;

	if (get_next_line(0, &line) < 1)
		exit(0);
	get_next_line(0, &line);
	tmp = line;
	line = ft_strtrim(tmp);
	ft_strdel(&tmp);
	cmd = ft_strtok(line, "\t ");
	ft_strdel(&line);
	return (cmd);
}

void	update_wd(t_env **env, char **wd)
{
	set_var(env, wd[0]);
	set_var(env, wd[1]);
	ft_strdel(&wd[0]);
	ft_strdel(&wd[1]);
}
