/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:38:09 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/18 14:41:44 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(t_env *env, char *arg, int n)
{
	int	len;

	len = 0;
	while (env && n)
	{
		if (!ft_strncmp(arg + 1, env->var_name, n))
		{
			ft_printf("%s", env->var_value);
			return ;
		}
		env = env->next;
	}
}

static	int	ft_len(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] != '$' && arg[len])
		len++;
	return (len);
}

static void	echo_loop(char **args, int i, int j, t_env **env)
{
	int	n;

	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j])
			{
				n = ft_len(args[i] + j + 1);
				print_env_var(*env, args[i] + j, n);
				(args[i][j] == '$' && !args[i][j + 1]) ? ft_putchar('$') : 0;
				j += n + 1;
				if (args[i][j + ft_strlen(args[i] + j)])
					break ;
			}
			else
			{
				while (args[i][j] && args[i][j] != '$')
					j += ft_putchar(args[i][j]);
			}
		}
		i++;
		(args[i]) ? ft_putchar(' ') : 0;
	}
}

int			ft_echo(t_env **env, char **args)
{
	int	new_line;
	int	i;
	int	j;

	i = 1;
	new_line = 1;
	j = 0;
	if (args[1] && !ft_strcmp("-n", args[1]))
	{
		new_line = 0;
		i++;
	}
	echo_loop(args, i, j, env);
	(new_line) ? ft_putchar('\n') : 0;
	return (0);
}
