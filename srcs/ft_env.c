/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:51:23 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/02 15:06:24 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_usage(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: env [-i] [-u name]\n\t   [name=value ...]\n", 2);
	return (1);
}

char		**env_to_tab(t_env *env)
{
	char	**tab;
	t_env	*ptr;
	int		i;

	i = 0;
	tab = NULL;
	ptr = env;
	if (!(tab = (char**)malloc((size_env(env) + 1) * sizeof(char*))))
		ft_perror("malloc");
	while (env)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(env->var_value) +
							ft_strlen(env->var_name) + 2))))
			ft_perror("malloc");
		ft_strcpy(tab[i], env->var_name);
		ft_strcat(tab[i], "=");
		ft_strcat(tab[i++], env->var_value);
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int			display_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->var_name, env->var_value);
		env = env->next;
	}
	return (0);
}

t_env		*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int			ft_env(t_env **env, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		return (display_env(*env));
	if (args[1][0] == '-' &&
			ft_strcmp(args[1], "-i") && ft_strcmp(args[1], "-u"))
		return (ft_env_usage(args[1][1]));
	if (args[1] && !ft_strcmp(args[1], "-i"))
		return (0);
	return (0);
}
