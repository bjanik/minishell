/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:38:09 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/24 13:19:17 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(t_env *env, char *arg)
{
	while (env)
	{
		if (!ft_strcmp(arg + 1, env->var_name))
		{
			ft_printf("%s", env->var_value);
			return ;
		}
		env = env->next;
	}
}

/*void	list_files(void)
{
	DIR				*dir_stream;
	struct dirent	 *dir_content;
	
	if (!(dir_stream = opendir(".")))
		return ;
	while ((dir_content = readdir(dir_stream)))
	{
		if (dir_content->d_name[0] != '.')
			ft_printf("%s ", dir_content->d_name);
	}
	closedir(dir_stream);
}*/

int			ft_echo(t_env **env, char **args)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (args[1] && !ft_strcmp("-n", args[1]))
	{
		new_line = 0;
		i = 2;
	}
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1])
			print_env_var(*env, args[i]);
		else
			ft_printf("%s", args[i]);
		i++;
		(args[i]) ? ft_putchar(' ') : 0;
	}
	ft_printf("%.*s", new_line, "\n");
	return (0);
}
