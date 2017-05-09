/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:52:11 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/09 19:48:50 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path(char *path, t_env *env, char **cmd)
{
	char	*pwd;
	char	*fullpath;
	char	*s;
	t_env	*p;

	p = ft_getenv(env, "HOME");
	if (!path || (path && !ft_strcmp(path, "~")))
		return (set_home_path(env, path));
	else if (cmd[1] && !ft_strcmp(cmd[1], "-"))
		return (set_oldpwd_path(env, path));
	else if ((s = ft_strchr(cmd[1], '~')) && p)
	{
		if (!(path = ft_memalloc(MAXPATHLEN)))
			ft_perror("malloc failed");
		ft_strcpy(path, p->var_value);
		ft_strcat(path, s + 1);
	}
	else if (cmd[1] && cmd[1][0] != '/')
	{
		pwd = getcwd(NULL, MAXPATHLEN);
		fullpath = ft_strnjoin(pwd, 2, "/", cmd[1]);
		free(pwd);
		return (fullpath);
	}
	return (path);
}

static int	ft_cd_error_msg(int error, char *cmd_arg, char **path)
{
	if (error == INEXISTENT)
		ft_error_msg("cd: no such file or directory: ", cmd_arg);
	if (error == MULTIPLE_ARGS)
		ft_error_msg("cd: string not in pwd: ", cmd_arg);
	if (error == PERMISSION)
		ft_error_msg("cd: permission denied: ", *path);
	if (error == NOT_DIRECTORY)
		ft_error_msg("cd: not a directory: ", cmd_arg);
	(cmd_arg != *path) ? ft_strdel(path) : 0;
	return (1);
}

static int	ft_cd_error(char **cmd_arg, char **path)
{
	struct stat	info;

	if (cmd_arg[1] && cmd_arg[2])
		return (ft_cd_error_msg(MULTIPLE_ARGS, cmd_arg[1], path));
	if (cmd_arg[1] && access(*path, F_OK) < 0)
		return (ft_cd_error_msg(INEXISTENT, cmd_arg[1], path));
	stat(*path, &info);
	if (!S_ISDIR(info.st_mode))
		return (ft_cd_error_msg(NOT_DIRECTORY, cmd_arg[1], path));
	if (cmd_arg[1] && access(*path, X_OK) < 0)
		return (ft_cd_error_msg(PERMISSION, cmd_arg[1], path));
	return (0);
}

int			ft_cd(t_env **env, char **cmd)
{
	char	*wd[2];
	char	*path;

	path = cmd[1];
	path = ft_get_path(path, *env, cmd);
	if (!path || ft_cd_error(cmd, &path))
		return (1);
	wd[0] = getcwd(NULL, MAXPATHLEN);
	wd[0] = ft_strjoin_and_free("OLDPWD=", wd[0], 2);
	chdir(path);
	wd[1] = getcwd(NULL, MAXPATHLEN);
	wd[1] = ft_strjoin_and_free("PWD=", wd[1], 2);
	update_wd(env, wd);
	(cmd[1] != path) ? ft_strdel(&path) : 0;
	return (0);
}
