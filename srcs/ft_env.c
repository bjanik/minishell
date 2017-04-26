/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:51:23 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/25 18:33:34 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->var_name, env->var_value);
		env = env->next;
	}
	return (0);
}

t_env	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}


int	ft_env(t_env **env, char **args)
{
	t_env	*mod_env;

	if (!args[1])
		return (display_env(*env));
	if (args[1] && !ft_strcmp(args[1], "-i"))
	{
		mod_env = modified_env(*env);
		clear_env(&mod_env);
		(!args[2]) ? display_env(mod_env) : 0;
		return (0);
	}
//	if (args[1] && ft_strcmp("-u", args[1])
	return (0);
}
