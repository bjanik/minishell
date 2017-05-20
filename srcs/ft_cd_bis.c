/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:14:03 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/20 17:55:01 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_home_path(t_env *env, char *path)
{
	t_env	*p;

	if ((p = ft_getenv(env, "HOME")))
		(!(path = ft_strdup(p->var_value))) ? ft_perror("malloc failed") : 0;
	else
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}

char	*set_oldpwd_path(t_env *env, char *path)
{
	t_env	*p;

	if ((p = ft_getenv(env, "OLDPWD")))
		(!(path = ft_strdup(p->var_value))) ? ft_perror("malloc failed") : 0;
	else
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	return (path);
}

void	update_wd(t_env **env, char **wd)
{
	set_var(env, wd[0]);
	set_var(env, wd[1]);
	ft_strdel(&wd[0]);
	ft_strdel(&wd[1]);
}
