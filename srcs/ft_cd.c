/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:52:11 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/01 17:10:21 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_concat_path(char *path, t_env *env)
{
	char	*pwd;
	char	*fullpath;
	char	*tmp;
	char	*s;
	t_env	*p;

	if ((s = ft_strchr(path, '~')))
	{
		tmp = path;
		path = ft_memalloc(MAXPATHLEN);
		if ((p = ft_getenv(env, "HOME")))
		{
			ft_strncpy(tmp, path, s - tmp + 1);
			ft_strcpy(path, p->var_value);
			ft_strcat(path, s + 1);
		}
		ft_strdel(&tmp);
		return (path);
	}
	pwd = getcwd(NULL, MAXPATHLEN);
	fullpath = ft_strnjoin(pwd, 2, "/", path);
	free(pwd);
	ft_strdel(&path);
	return (fullpath);
}

static int	ft_cd_error_msg(int error, char *cmd_arg, char **path)
{
	if (error == INEXISTENT)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(cmd_arg, 2);
	}
	if (error == MULTIPLE_ARGS)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(cmd_arg, 2);
	}
	if (error == PERMISSION)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(cmd_arg, 2);
	}
	ft_strdel(path);
	return (1);
}

static int	ft_cd_error(char **cmd_arg, char **path, t_env *env)
{
	if (cmd_arg[1])
		*path = ft_strdup(cmd_arg[1]);
	if (cmd_arg[1] && *path[0] != '/')
		*path = ft_concat_path(*path, env);
	if (cmd_arg[1] && cmd_arg[2])
		return (ft_cd_error_msg(MULTIPLE_ARGS, cmd_arg[1], path));
	if (cmd_arg[1] && access(*path, F_OK) < 0 &&
			ft_strcmp(cmd_arg[1], "~") && ft_strcmp(cmd_arg[1], "-"))
		return (ft_cd_error_msg(INEXISTENT, cmd_arg[1], path));
	if (cmd_arg[1] && access(*path, X_OK) < 0 &&
			ft_strcmp(cmd_arg[1], "~") && ft_strcmp(cmd_arg[1], "-"))
		return (ft_cd_error_msg(PERMISSION, cmd_arg[1], path));
	return (0);
}

void		update_wd(t_env **env, char **wd)
{
	set_var(env, wd[0]);
	set_var(env, wd[1]);
	ft_strdel(&wd[0]);
	ft_strdel(&wd[1]);
}

int			ft_cd(t_env **env, char **cmd_arg)
{
	t_env	*p;
	char	*wd[2];
	char	*path;

	path = NULL;
	if (ft_cd_error(cmd_arg, &path, *env))
		return (1);
	wd[0] = getcwd(NULL, MAXPATHLEN);
	wd[0] = ft_strjoin_and_free("OLDPWD=", wd[0], 2);
	if ((!cmd_arg[1] || !ft_strcmp(cmd_arg[1], "~")) &&
			(p = ft_getenv(*env, "HOME")))
		chdir(p->var_value);
	else if ((cmd_arg[1] && !ft_strcmp(cmd_arg[1], "-")) &&
			(p = ft_getenv(*env, "OLDPWD")))
		chdir(p->var_value);
	else
		chdir(path);
	wd[1] = getcwd(NULL, MAXPATHLEN);
	wd[1] = ft_strjoin_and_free("PWD=", wd[1], 2);
	update_wd(env, wd);
	ft_strdel(&path);
	return (0);
}
