/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:54:24 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/03 16:22:47 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setenv_no_value(char **split, char *var)
{
	if (!split[1] && !ft_strchr(var, '='))
	{
		ft_free_string_tab(&split);
		return (1);
	}
	return (0);
}

void		set_var(t_env **env, char *var)
{
	char	**spvar;
	t_env	*ptr;

	ptr = *env;
	spvar = ft_strsplit(var, '=');
	if (!var || setenv_no_value(spvar, var) == 1)
		return ;
	while (ptr)
	{
		if (!spvar[1] && !ft_strcmp(ptr->var_name, spvar[0]))
		{
			ptr->var_value = ft_strdup("");
			return ;
		}
		if ((!ft_strcmp(ptr->var_name, spvar[0])))
		{
			ft_strdel(&ptr->var_value);
			ptr->var_value = (spvar[1]) ? ft_strdup(spvar[1]) : ft_strdup("");
			ft_free_string_tab(&spvar);
			return ;
		}
		ptr = ptr->next;
	}
	push_back_env(env, var);
	ft_free_string_tab(&spvar);
}

int			ft_setenv(t_env **env, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[0] && !cmd[1])
	{
		ft_putendl_fd("setenv : not enough arguments", 2);
		return (-1);
	}
	while (cmd[i])
		set_var(env, cmd[i++]);
	return (0);
}
