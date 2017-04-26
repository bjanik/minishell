/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:52:11 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/26 17:51:39 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_concat_path(char *path)
{
	char	*pwd;
	char	*fullpath;
	char	*tmp;
	
	pwd = getcwd(NULL, MAXPATHLEN);
	fullpath = ft_strjoin(pwd, "/");
	tmp = fullpath;
	fullpath = ft_strjoin(fullpath, path);
	free(tmp);
	free(pwd);
	ft_strdel(&path);
	return (fullpath);
}

static int	ft_cd_error_msg(int error, char *cmd_arg, char **path)
{
	if (error == INEXISTENT)
		ft_printf("cd : no such file or directory: %s\n", cmd_arg);
	if (error == MULTIPLE_ARGS)
		ft_printf("cd : string not in pwd: %s\n", cmd_arg);
	if (error == PERMISSION)
		ft_printf("cd : permission denied: %s\n", cmd_arg);
	ft_strdel(path);
	return (1);
}

static int	ft_cd_error(char **cmd_arg, char **path)
{
	if (cmd_arg[1])
		*path = ft_strdup(cmd_arg[1]);
	if (cmd_arg[1] && *path[0] != '/')
		*path = ft_concat_path(*path);
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

void	update_wd(t_env **env, char **wd)
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
	if (ft_cd_error(cmd_arg, &path))
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
